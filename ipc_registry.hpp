/**
 * @file   ipc_registry.hpp
 * @brief  Inter-process communication registry — module descriptors,
 *         arbitration policy and watchdog service configuration.
 *
 * @author carlos
 * @date   2025-01
 *
 * @ref    CE78 Título III Cap.1 arts.66-80 | Título IX arts.159-165
 *         LO 2/1979 TC | LO 3/1981 Defensor del Pueblo
 */

#ifndef IPC_REGISTRY_HPP
#define IPC_REGISTRY_HPP

#include <cstdint>
#include <array>

// ============================================================================
//  MODULE: legislature_bus
//  Bicameral message-passing bus — Título III Cap.1 (arts. 66-80)
//  Scope: TAI/GSI exam — arts. 66-80 only
// ============================================================================

namespace legislature_bus {

    /* art. 66 — bus descriptor
     * "1. Las Cortes Generales representan al pueblo español y están formadas
     *    por el Congreso de los Diputados y el Senado.
     *  2. Las Cortes Generales ejercen la potestad legislativa del Estado,
     *    aprueban sus Presupuestos, controlan la acción del Gobierno y tienen
     *    las demás competencias que les atribuya la Constitución.
     *  3. Las Cortes Generales son inviolables." */
    static constexpr uint8_t  BUS_CHANNEL_COUNT  = 2;   // Congreso + Senado
    static constexpr bool     BUS_INVIOLABLE      = true;

    enum class Channel : uint8_t {
        LOWER = 0,   // Congreso de los Diputados — Cámara Baja
        UPPER = 1,   // Senado                    — Cámara Alta
    };

    /* art. 67 — session constraints
     * "1. Nadie podrá ser miembro de las dos Cámaras simultáneamente, ni
     *    acumular el acta de una Asamblea de Comunidad Autónoma con la de
     *    Diputado al Congreso.
     *  2. Los miembros de las Cortes Generales no estarán ligados por mandato
     *    imperativo.
     *  3. Las reuniones de Parlamentarios que se celebren sin convocatoria
     *    reglamentaria no vincularán a las Cámaras, y no podrán ejercer sus
     *    funciones ni ostentar sus privilegios." */
    static constexpr bool DUAL_CHANNEL_MEMBERSHIP_ALLOWED    = false;  // art.67.1
    static constexpr bool IMPERATIVE_MANDATE_ENFORCED        = false;  // art.67.2
    static constexpr bool UNSCHEDULED_SESSION_BINDING        = false;  // art.67.3


    // -----------------------------------------------------------------------
    //  LOWER CHANNEL — Congreso de los Diputados (art. 68)
    // -----------------------------------------------------------------------

    namespace lower_channel {

        /* art. 68 — node count and election spec
         * "1. El Congreso se compone de un mínimo de 300 y un máximo de 400
         *    Diputados, elegidos por sufragio universal, libre, igual, directo
         *    y secreto, en los términos que establezca la ley.
         *  2. La circunscripción electoral es la provincia. Las poblaciones de
         *    Ceuta y Melilla estarán representadas cada una de ellas por un
         *    Diputado. La ley distribuirá el número total de Diputados,
         *    asignando una representación mínima inicial a cada circunscripción
         *    y distribuyendo los demás en proporción a la población.
         *  3. La elección se verificará en cada circunscripción atendiendo a
         *    criterios de representación proporcional.
         *  4. El Congreso es elegido por cuatro años. El mandato de los
         *    Diputados termina cuatro años después de su elección o el día de
         *    la disolución de la Cámara.
         *  5. Son electores y elegibles todos los españoles que estén en pleno
         *    uso de sus derechos políticos. La ley reconocerá y el Estado
         *    facilitará el ejercicio del derecho de sufragio a los españoles que
         *    se encuentren fuera del territorio de España.
         *  6. Las elecciones tendrán lugar entre los treinta días y sesenta días
         *    desde la terminación del mandato. El Congreso electo deberá ser
         *    convocado dentro de los veinticinco días siguientes a la
         *    celebración de las elecciones." */

        static constexpr uint16_t NODE_COUNT_MIN     = 300;
        static constexpr uint16_t NODE_COUNT_MAX     = 400;
        static constexpr uint16_t NODE_COUNT_CURRENT = 350;  // per LOREG
        static constexpr uint8_t  TERM_YEARS         = 4;

        // Circumscription layout
        static constexpr const char* DISTRICT_UNIT = "provincia";
        static constexpr uint8_t  CEUTA_SEATS      = 1;
        static constexpr uint8_t  MELILLA_SEATS     = 1;
        static constexpr const char* ALLOC_METHOD  = "proportional to population";

        // Election timing (art. 68.6)
        static constexpr uint8_t ELECTION_WINDOW_MIN_DAYS = 30;
        static constexpr uint8_t ELECTION_WINDOW_MAX_DAYS = 60;
        static constexpr uint8_t CONVENE_AFTER_ELECTION_DAYS = 25;

        /* Exclusive functions of the lower channel (various arts.):
         *  · art. 99  — approve/reject PM candidate proposed by the King
         *  · arts.112-114 — vote of confidence / motion of no-confidence
         *  · art. 86  — validate or repeal decree-laws (extraordinary + urgent need)
         *  · art. 116 — authorize alarm-state extension + exception-state declaration
         *  · art. 116 — declare state of siege (mayoría absoluta)
         *  · art. 102.2 — initiate prosecution of PM/ministers for treason
         *  · art. 92  — authorize consultative referendum */
        enum class ExclusiveOp : uint8_t {
            APPROVE_PM_CANDIDATE          = 0,  // art.99
            VOTE_CONFIDENCE_OR_CENSURE    = 1,  // arts.112-114
            VALIDATE_DECREE_LAWS          = 2,  // art.86
            AUTHORIZE_EMERGENCY_STATES    = 3,  // art.116
            DECLARE_SIEGE                 = 4,  // art.116 — abs. majority
            INITIATE_PM_PROSECUTION       = 5,  // art.102.2
            AUTHORIZE_REFERENDUM          = 6,  // art.92
        };
    } // namespace lower_channel


    // -----------------------------------------------------------------------
    //  UPPER CHANNEL — Senado (art. 69)
    //  ⚠️  art.69.3 amended 2026-05-19: Ibiza and Formentera split
    // -----------------------------------------------------------------------

    namespace upper_channel {

        /* art. 69 — territorial representation chamber
         * "1. El Senado es la Cámara de representación territorial.
         *  2. En cada provincia se elegirán cuatro Senadores por sufragio
         *    universal, libre, igual, directo y secreto.
         *  3. En las provincias insulares, cada isla o agrupación de ellas,
         *    con Cabildo o Consejo Insular, constituirá una circunscripción,
         *    correspondiendo tres a cada una de las islas mayores —Gran Canaria,
         *    Mallorca y Tenerife— y uno a cada una de las siguientes islas:
         *    Ibiza, Formentera, Menorca, Fuerteventura, Gomera, Hierro,
         *    Lanzarote y La Palma.      ← TEXTO REFORMADO 2026
         *  4. Las poblaciones de Ceuta y Melilla elegirán cada una dos Senadores.
         *  5. Las Comunidades Autónomas designarán además un Senador y otro más
         *    por cada millón de habitantes de su respectivo territorio. La
         *    designación corresponderá a la Asamblea legislativa o, en su defecto,
         *    al órgano colegiado superior de la Comunidad Autónoma, asegurando
         *    la adecuada representación proporcional.
         *  6. El Senado es elegido por cuatro años." */

        static constexpr uint8_t TERM_YEARS = 4;

        // Seat allocation by district type
        static constexpr uint8_t SEATS_PER_PROVINCE        = 4;
        static constexpr uint8_t SEATS_MAJOR_ISLANDS        = 3;  // Gran Canaria, Mallorca, Tenerife
        static constexpr uint8_t SEATS_MINOR_ISLANDS        = 1;  // all others incl. Ibiza & Formentera (post-2026)
        static constexpr uint8_t SEATS_CEUTA               = 2;
        static constexpr uint8_t SEATS_MELILLA              = 2;
        // Autonomous communities: 1 base + 1 per million inhabitants

        // Informational totals (not required for exam)
        static constexpr uint16_t APPROX_PROVINCIAL_SEATS  = 208;
        static constexpr uint16_t APPROX_AUTONOMIC_SEATS   =  58;
        static constexpr uint16_t APPROX_TOTAL             = 266;

    } // namespace upper_channel


    // -----------------------------------------------------------------------
    //  COMMON BUS CONSTRAINTS (arts. 70-80)
    // -----------------------------------------------------------------------

    /* art. 70 — ineligibility and incompatibility
     * "La ley electoral determinará las causas de inelegibilidad e
     *  incompatibilidad de los Diputados y Senadores, que comprenderán
     *  en todo caso:
     *  a) A los componentes del Tribunal Constitucional.
     *  b) A los altos cargos de la Administración del Estado que determine
     *     la ley, con la excepción de los miembros del Gobierno.
     *  c) Al Defensor del Pueblo.
     *  d) A los Magistrados, Jueces y Fiscales en activo.
     *  e) A los militares profesionales y miembros de las Fuerzas y Cuerpos
     *     de Seguridad y Policía en activo.
     *  f) A los miembros de las Juntas Electorales." */
    enum class IneligibleRole : uint8_t {
        TC_MEMBER              = 0,  // a
        SENIOR_CIVIL_SERVANT   = 1,  // b (except cabinet ministers)
        OMBUDSMAN              = 2,  // c
        JUDGE_OR_PROSECUTOR    = 3,  // d (active)
        MILITARY_OR_POLICE     = 4,  // e (active)
        ELECTORAL_BOARD_MEMBER = 5,  // f
    };

    /* art. 71 — member privileges
     * "1. Los Diputados y Senadores gozarán de inviolabilidad por las
     *    opiniones manifestadas en el ejercicio de sus funciones.
     *  2. Durante el período de su mandato gozarán de inmunidad y sólo podrán
     *    ser detenidos en caso de flagrante delito. No podrán ser inculpados ni
     *    procesados sin la previa autorización de la Cámara respectiva.
     *  3. En las causas contra Diputados y Senadores será competente la Sala
     *    de lo Penal del Tribunal Supremo.
     *  4. Los Diputados y Senadores percibirán una asignación fijada por las
     *    respectivas Cámaras." */
    static constexpr bool MEMBER_INVIOLABLE             = true;   // opinions in office
    static constexpr bool MEMBER_IMMUNE_FROM_ARREST     = true;   // except flagrante
    static constexpr bool PROSECUTION_NEEDS_CHAMBER_AUTH = true;
    static constexpr const char* CRIMINAL_JURISDICTION  = "Sala Penal — Tribunal Supremo";

    /* art. 72 — internal governance
     * "1. Las Cámaras establecen sus propios Reglamentos, aprueban
     *    autónomamente sus presupuestos y, de común acuerdo, regulan el
     *    Estatuto del Personal de las Cortes Generales.
     *    Los Reglamentos y su reforma requerirán mayoría absoluta.
     *  2. Las Cámaras eligen sus respectivos Presidentes y los demás miembros
     *    de sus Mesas. Las sesiones conjuntas serán presididas por el Presidente
     *    del Congreso.
     *  3. Los Presidentes ejercen en nombre de las Cámaras todos los poderes
     *    administrativos y facultades de policía en sus respectivas sedes." */
    static constexpr const char* JOINT_SESSION_CHAIR    = "Presidente del Congreso";
    static constexpr const char* RULES_MAJORITY         = "mayoría absoluta";

    /* art. 73 — session calendar
     * "1. Las Cámaras se reunirán anualmente en dos períodos ordinarios:
     *    el primero, de septiembre a diciembre, y el segundo, de febrero a junio.
     *  2. Las Cámaras podrán reunirse en sesiones extraordinarias a petición
     *    del Gobierno, de la Diputación Permanente o de la mayoría absoluta
     *    de los miembros de cualquiera de las Cámaras. Las sesiones
     *    extraordinarias deberán convocarse sobre un orden del día determinado
     *    y serán clausuradas una vez que éste haya sido agotado." */
    static constexpr uint8_t ORDINARY_SESSIONS_PER_YEAR = 2;
    // Period 1: September → December
    // Period 2: February  → June
    // Extraordinary sessions: requested by Gobierno | Diputación Permanente | abs. majority

    /* art. 74 — joint sessions
     * "1. Las Cámaras se reunirán en sesión conjunta para ejercer las
     *    competencias no legislativas que el Título II atribuye a las Cortes.
     *  2. Las decisiones de los arts. 94.1, 145.2 y 158.2 se adoptarán por
     *    mayoría de cada Cámara. En el primer caso inicia el Congreso; en los
     *    otros dos el Senado. Si no hay acuerdo: Comisión Mixta paritaria.
     *    Si tampoco: decide el Congreso por mayoría absoluta." */
    static constexpr const char* JOINT_SESSION_SCOPE    = "non-legislative Title-II functions";
    static constexpr const char* DEADLOCK_RESOLVER      = "Congreso — mayoría absoluta";

    /* art. 75 — committee delegation
     * "1. Las Cámaras funcionarán en Pleno y por Comisiones.
     *  2. Las Cámaras podrán delegar en las Comisiones Legislativas Permanentes
     *    la aprobación de proyectos o proposiciones de ley. El Pleno podrá
     *    recabar en cualquier momento el debate.
     *  3. Quedan exceptuados de lo dispuesto en el apartado anterior:
     *    la reforma constitucional, las cuestiones internacionales, las leyes
     *    orgánicas y de bases y los Presupuestos Generales del Estado." */
    // Items that CANNOT be delegated to committee:
    enum class NonDelegable : uint8_t {
        CONSTITUTIONAL_REFORM    = 0,
        INTERNATIONAL_MATTERS    = 1,
        ORGANIC_AND_BASIC_LAWS   = 2,
        GENERAL_STATE_BUDGET     = 3,
    };

    /* art. 76 — investigation committees
     * "1. El Congreso y el Senado podrán nombrar Comisiones de investigación
     *    sobre cualquier asunto de interés público. Sus conclusiones no serán
     *    vinculantes para los Tribunales, ni afectarán a las resoluciones
     *    judiciales, sin perjuicio de que el resultado sea comunicado al
     *    Ministerio Fiscal.
     *  2. Será obligatorio comparecer a requerimiento de las Cámaras." */
    static constexpr bool COMMITTEE_CONCLUSIONS_BIND_COURTS = false;
    static constexpr bool APPEARANCE_ON_REQUEST_MANDATORY   = true;

    /* art. 77 — petition handling
     * "1. Las Cámaras pueden recibir peticiones individuales y colectivas,
     *    siempre por escrito, quedando prohibida la presentación directa por
     *    manifestaciones ciudadanas.
     *  2. Las Cámaras pueden remitir al Gobierno las peticiones que reciban.
     *    El Gobierno está obligado a explicarse sobre su contenido, siempre
     *    que las Cámaras lo exijan." */
    static constexpr bool PETITIONS_MUST_BE_WRITTEN         = true;
    static constexpr bool DIRECT_CITIZEN_DEMO_AT_CHAMBER    = false;

    /* art. 78 — standing committee (Diputación Permanente)
     * "1. En cada Cámara habrá una Diputación Permanente compuesta por un
     *    mínimo de veintiún miembros, que representarán a los grupos
     *    parlamentarios en proporción a su importancia numérica.
     *  2. Estarán presididas por el Presidente de la Cámara respectiva y
     *    tendrán como funciones las del art.73, asumir las facultades de las
     *    Cámaras según arts.86 y 116 si éstas hubiesen sido disueltas o hubiere
     *    expirado su mandato, y velar por los poderes de las Cámaras cuando no
     *    estén reunidas.
     *  3. Expirado el mandato o disuelta la Cámara, las Diputaciones Permanentes
     *    seguirán ejerciendo sus funciones hasta la constitución de las nuevas
     *    Cortes.
     *  4. Reunida la Cámara, la Diputación Permanente dará cuenta de los asuntos
     *    tratados y sus decisiones." */
    static constexpr uint8_t STANDING_COMMITTEE_MIN_MEMBERS = 21;

    /* art. 79 — quorum and voting
     * "1. Para adoptar acuerdos, las Cámaras deben estar reunidas
     *    reglamentariamente y con asistencia de la mayoría de sus miembros.
     *  2. Los acuerdos deberán ser aprobados por la mayoría de los miembros
     *    presentes, sin perjuicio de las mayorías especiales que establezcan
     *    la Constitución o las leyes orgánicas.
     *  3. El voto de Senadores y Diputados es personal e indelegable." */
    static constexpr const char* QUORUM_REQUIRED   = "mayoría de los miembros";
    static constexpr const char* DEFAULT_MAJORITY  = "mayoría de presentes";
    static constexpr bool VOTE_DELEGABLE           = false;  // art.79.3

    /* art. 80 — plenary sessions default visibility
     * "Las sesiones plenarias de las Cámaras serán públicas, salvo acuerdo en
     *  contrario de cada Cámara, adoptado por mayoría absoluta o con arreglo
     *  al Reglamento." */
    static constexpr bool PLENARY_SESSION_PUBLIC_DEFAULT = true;
    static constexpr const char* CLOSED_SESSION_REQUIRES = "abs. majority or Reglamento";

} // namespace legislature_bus


// ============================================================================
//  MODULE: arbitration_core
//  Constitutional arbitrator — Título IX arts.159-165 + LO 2/1979
//  ⭐  Key numbers: 12 members | 9-year term | renew 1/3 every 3 years
// ============================================================================

namespace arbitration_core {

    /* art. 159.1 — composition rule (12 = 4+4+2+2)
     * "El Tribunal Constitucional se compone de 12 miembros nombrados por el
     *  Rey; de ellos, cuatro a propuesta del Congreso por mayoría de tres
     *  quintos de sus miembros; cuatro a propuesta del Senado, con idéntica
     *  mayoría; dos a propuesta del Gobierno, y dos a propuesta del Consejo
     *  General del Poder Judicial." */
    static constexpr uint8_t TOTAL_MEMBERS          = 12;
    static constexpr uint8_t FROM_CONGRESO           =  4;  // 3/5 majority
    static constexpr uint8_t FROM_SENADO             =  4;  // 3/5 majority
    static constexpr uint8_t FROM_GOBIERNO           =  2;
    static constexpr uint8_t FROM_CGPJ               =  2;
    static constexpr const char* APPOINTED_BY        = "El Rey";

    /* art. 159.2 — eligibility requirements
     * "Los miembros deberán ser nombrados entre Magistrados y Fiscales,
     *  Profesores de Universidad, funcionarios públicos y Abogados, todos
     *  ellos juristas de reconocida competencia con más de quince años de
     *  ejercicio profesional." */
    static constexpr uint8_t MIN_YEARS_EXPERIENCE    = 15;
    enum class EligibleProfile : uint8_t {
        MAGISTRATE_OR_PROSECUTOR = 0,
        UNIVERSITY_PROFESSOR     = 1,
        CIVIL_SERVANT            = 2,
        LAWYER                   = 3,
    };

    /* art. 159.3 — term and renewal
     * "Los miembros serán designados por un período de nueve años y se
     *  renovarán por terceras partes cada tres." */
    static constexpr uint8_t TERM_YEARS              = 9;
    static constexpr uint8_t RENEWAL_FRACTION_DENOM  = 3;  // 1/3 every 3 years
    static constexpr uint8_t RENEWAL_PERIOD_YEARS    = 3;
    // Ningún Magistrado puede ser propuesto para otro período inmediato,
    // SALVO que hubiera ocupado el cargo por un plazo no superior a 3 años.
    static constexpr uint8_t REAPPOINTMENT_EXCEPTION_MAX_YEARS = 3;

    /* art. 159.4 — incompatibilities
     * "La condición de miembro es incompatible con:
     *  · todo mandato representativo
     *  · cargos políticos o administrativos
     *  · funciones directivas en partido político o sindicato
     *  · ejercicio de las carreras judicial y fiscal
     *  · cualquier actividad profesional o mercantil
     *  En lo demás tendrán las incompatibilidades de los miembros del PJ." */
    enum class Incompatible : uint8_t {
        REPRESENTATIVE_MANDATE  = 0,
        POLITICAL_ADMIN_OFFICE  = 1,
        PARTY_OR_UNION_DIRECTORSHIP = 2,
        JUDICIAL_OR_FISCAL_CAREER   = 3,
        ANY_PROFESSIONAL_ACTIVITY   = 4,
    };

    /* art. 159.5 — independence and security of tenure
     * "Los miembros del Tribunal Constitucional serán independientes e
     *  inamovibles en el ejercicio de su mandato." */
    static constexpr bool MEMBERS_INDEPENDENT   = true;
    static constexpr bool MEMBERS_IRREMOVABLE   = true;

    // Grounds for removal (LO 2/1979):
    // · renuncia aceptada por el Presidente del TC
    // · expiración del plazo
    // · incapacidad prevista para miembros del PJ
    // · incompatibilidad sobrevenida
    // · dejar de atender con diligencia los deberes del cargo
    // · violar la reserva propia de su función
    // · haber sido declarado responsable civilmente por dolo o condenado
    //   por delito doloso o por culpa grave

    /* art. 160 — presidency
     * "El Presidente del Tribunal Constitucional será nombrado entre sus
     *  miembros por el Rey, a propuesta del mismo Tribunal en pleno y por
     *  un período de tres años." */
    static constexpr uint8_t  PRESIDENT_TERM_YEARS   = 3;
    static constexpr bool     PRESIDENT_REELECTABLE  = true;  // once
    static constexpr const char* PRESIDENT_PROPOSED_BY = "Tribunal en Pleno — votación secreta";
    static constexpr const char* PRESIDENT_APPOINTED_BY = "El Rey";
    // Vicepresidente: elected same way; presides Sala Segunda; substitutes President

    /* art. 161 — jurisdiction (art. 161 CE)
     * "1. El Tribunal Constitucional tiene jurisdicción en todo el territorio
     *    español y es competente para conocer:
     *    a) Del recurso de inconstitucionalidad contra leyes y disposiciones
     *       normativas con fuerza de ley.
     *    b) Del recurso de amparo por violación de los derechos y libertades
     *       referidos en el art.53.2.
     *    c) De los conflictos de competencia entre el Estado y las CC.AA.
     *       o de las CC.AA. entre sí.
     *    d) De las demás materias que le atribuyan la CE o las leyes orgánicas.
     *  2. El Gobierno podrá impugnar ante el TC las disposiciones y resoluciones
     *    de los órganos de las CC.AA. La impugnación producirá la suspensión;
     *    el TC deberá ratificarla o levantarla en un plazo no superior a 5 meses." */
    static constexpr uint8_t  CCAA_SUSPENSION_REVIEW_MAX_MONTHS = 5;

    /* art. 162 — standing to bring actions
     * "1. Están legitimados:
     *    a) Para el recurso de inconstitucionalidad:
     *       · Presidente del Gobierno
     *       · Defensor del Pueblo
     *       · 50 Diputados
     *       · 50 Senadores
     *       · Órganos colegiados ejecutivos de las CC.AA.
     *       · Asambleas de las CC.AA.
     *    b) Para el recurso de amparo:
     *       · Toda persona natural o jurídica con interés legítimo
     *       · Defensor del Pueblo
     *       · Ministerio Fiscal" */
    static constexpr uint8_t MIN_DEPUTIES_FOR_UNCONSTITUTIONALITY = 50;
    static constexpr uint8_t MIN_SENATORS_FOR_UNCONSTITUTIONALITY = 50;

    /* art. 163 — preliminary reference (cuestión de inconstitucionalidad)
     * "Cuando un órgano judicial considere, en algún proceso, que una norma
     *  con rango de ley, aplicable al caso, de cuya validez dependa el fallo,
     *  pueda ser contraria a la Constitución, planteará la cuestión ante el
     *  Tribunal Constitucional en los supuestos, en la forma y con los efectos
     *  que establezca la ley, que en ningún caso serán suspensivos." */
    static constexpr bool PRELIMINARY_REF_SUSPENDS_PROCEEDINGS = false;

    /* art. 164 — ruling properties
     * "1. Las sentencias del Tribunal Constitucional se publicarán en el BOE
     *    con los votos particulares, si los hubiere.
     *    Tienen el valor de cosa juzgada a partir del día siguiente de su
     *    publicación y no cabe recurso alguno contra ellas.
     *    Las que declaren la inconstitucionalidad de una ley o norma con fuerza
     *    de ley, y todas las que no se limiten a la estimación subjetiva de un
     *    derecho, tienen plenos efectos frente a todos (erga omnes).
     *  2. Salvo que en el fallo se disponga otra cosa, subsistirá la vigencia
     *    de la ley en la parte no afectada por la inconstitucionalidad." */
    static constexpr bool RULING_PUBLISHED_BOE              = true;
    static constexpr bool RULING_RES_JUDICATA_NEXT_DAY      = true;  // día siguiente
    static constexpr bool RULING_APPEALABLE                 = false;
    static constexpr bool UNCONSTITUTIONALITY_ERGA_OMNES    = true;
    static constexpr bool UNAFFECTED_PART_STAYS_IN_FORCE    = true;  // art.164.2

    /* art. 165 — framework law
     * "Una ley orgánica regulará el funcionamiento del Tribunal Constitucional,
     *  el estatuto de sus miembros, el procedimiento ante el mismo y las
     *  condiciones para el ejercicio de las acciones."
     *  → LO 2/1979, de 3 de octubre */
    static constexpr const char* FRAMEWORK_LAW = "LO 2/1979, de 3 de octubre, del TC";


    // -----------------------------------------------------------------------
    //  INTERNAL STRUCTURE (LO 2/1979)
    // -----------------------------------------------------------------------

    /* Operating modes:
     *
     *  PLENO  — all 12 Magistrados
     *           Presided by Presidente; fallback: Vicepresidente; fallback: most senior.
     *           Handles the most important matters (see below).
     *
     *  SALA   — 2 chambers of 6 Magistrados each, assigned by Pleno
     *           Sala Primera: presided by the Presidente del TC
     *           Sala Segunda: presided by the Vicepresidente
     *
     *  SECCIÓN — 3 members (President of the room + 2 Magistrados)
     *            Formed by each Sala (and the Pleno).
     *            Purpose: routine business + admissibility/inadmissibility decisions
     *
     *  Layout: Pleno → [Sala I, Sala II] → [Secc.I, Secc.II | Secc.III, Secc.IV]
     */

    enum class OperatingMode : uint8_t {
        PLENO    = 0,  // 12 members
        SALA     = 1,  // 6 members
        SECCION  = 2,  // 3 members
    };

    static constexpr uint8_t SALAS_COUNT     = 2;
    static constexpr uint8_t MEMBERS_PER_SALA = 6;
    static constexpr uint8_t MEMBERS_PER_SECCION = 3;  // president of room + 2


    // Matters reserved to the Pleno (LO 2/1979):
    // · Constitutionality/unconstitutionality of international treaties
    // · Recursos de inconstitucionalidad (except routine-doctrine ones → Sala)
    // · Cuestiones de inconstitucionalidad reserved by the Pleno itself
    // · Competence conflicts between State and CC.AA.
    // · Preliminary unconstitutionality reviews of autonomy statute drafts
    // · Impugnaciones del art.161.2 CE
    // · Conflicts between constitutional organs of the State
    // · Conflicts in defence of local autonomy
    // · Verification of Magistrado appointment requirements
    // · Assignment of Magistrados to each Sala
    // · Recusación and cese of Magistrados
    // · Approval and modification of TC regulations
    // · TC budget (integrated as independent section within PGE)


    // Full jurisdiction list (LO 2/1979 art.2):
    enum class Jurisdiction : uint8_t {
        UNCONSTITUTIONALITY_ACTION      = 0,  // recurso + cuestión de inconstitucionalidad
        AMPARO                          = 1,  // art.53.2 rights
        STATE_CCAA_COMPETENCE_CONFLICT  = 2,
        INTER_CCAA_COMPETENCE_CONFLICT  = 3,
        CONSTITUTIONAL_ORGAN_CONFLICT   = 4,
        LOCAL_AUTONOMY_DEFENCE          = 5,
        INTERNATIONAL_TREATY_REVIEW     = 6,
        PRIOR_STATUTE_REVIEW            = 7,  // art.79 LO 2/1979
        CCAA_CHALLENGE_ART161_2         = 8,
        MAGISTRADO_APPOINTMENT_VERIFY   = 9,
        OTHER_ORGANIC_LAW_MATTERS       = 10,
    };

} // namespace arbitration_core


// ============================================================================
//  MODULE: watchdog_service
//  System ombudsman — art. 54 CE + LO 3/1981 (6 April)
//  ⭐  5-year term | 3/5 majority | 2 deputies
// ============================================================================

namespace watchdog_service {

    /* art. 54 CE
     * "Una ley orgánica regulará la institución del Defensor del Pueblo, como
     *  alto comisionado de las Cortes Generales, designado por éstas para la
     *  defensa de los derechos comprendidos en este Título, a cuyo efecto
     *  podrá supervisar la actividad de la Administración, dando cuenta a
     *  las Cortes Generales."
     *
     *  → LO 3/1981, de 6 de abril, del Defensor del Pueblo */
    static constexpr const char* ROLE        = "Alto Comisionado de las Cortes Generales";
    static constexpr const char* SCOPE       = "Título I CE — all rights therein";
    static constexpr const char* REPORTS_TO  = "Cortes Generales";
    static constexpr const char* FRAMEWORK_LAW = "LO 3/1981, de 6 de abril";

    // --- ELECTION AND TERM ---
    /* LO 3/1981:
     * "El Defensor del Pueblo será elegido por las Cortes Generales para un
     *  periodo de cinco años."
     *  Election: Congreso + Senado jointly, 3/5 majority (as general rule).
     *  Communicates with the Cortes via Presidentes del Congreso y del Senado.
     *  A joint Comisión Mixta Congreso-Senado liaises with the institution. */
    static constexpr uint8_t TERM_YEARS        = 5;   // ⭐ 5 AÑOS — examen frecuente
    static constexpr const char* ELECTED_BY    = "Cortes Generales — Congreso + Senado";
    static constexpr const char* ELECTION_MAJORITY = "3/5 de cada Cámara (regla general)";
    static constexpr const char* TAKES_OFFICE_BEFORE = "mesas de ambas Cámaras";

    // --- ELIGIBILITY ---
    /* "Podrá ser elegido Defensor del Pueblo cualquier español mayor de edad
     *  que se encuentre en el pleno disfrute de sus derechos civiles y políticos." */
    static constexpr bool MUST_BE_SPANISH    = true;
    static constexpr uint8_t MIN_AGE         = 18;
    static constexpr bool MUST_HAVE_FULL_RIGHTS = true;

    // --- INCOMPATIBILITIES ---
    /* LO 3/1981:
     * "La condición de Defensor del Pueblo es incompatible con:
     *  · todo mandato representativo
     *  · todo cargo político o actividad de propaganda política
     *  · permanencia en el servicio activo de cualquier Administración pública
     *  · afiliación a partido político o desempeño de funciones directivas
     *    en partido político, sindicato, asociación o fundación
     *  · empleo al servicio de los mismos
     *  · ejercicio de las carreras judicial y fiscal
     *  · cualquier actividad profesional, liberal, mercantil o laboral" */
    enum class Incompatible : uint8_t {
        REPRESENTATIVE_MANDATE    = 0,
        POLITICAL_OFFICE_OR_PROP  = 1,
        ACTIVE_CIVIL_SERVICE      = 2,
        PARTY_UNION_AFFILIATION   = 3,
        JUDICIAL_OR_FISCAL_CAREER = 4,
        ANY_PROFESSIONAL_ACTIVITY = 5,
    };

    // --- PREROGATIVES ---
    /* LO 3/1981:
     * · No subject to imperative mandate. Receives no instructions from any authority.
     *   Acts with autonomy and according to own criteria.
     * · Enjoys inviolability — cannot be detained, disciplined, fined, prosecuted
     *   or judged for opinions or acts performed in the exercise of office.
     * · Immunity: cannot be detained or held except in flagrante delicto.
     *   Any decision on prosecution, imprisonment or trial belongs exclusively to
     *   the Sala de lo Penal del Tribunal Supremo. */
    static constexpr bool SUBJECT_TO_IMPERATIVE_MANDATE = false;
    static constexpr bool INVIOLABLE                     = true;
    static constexpr bool IMMUNE_FROM_ARREST             = true;   // except flagrante
    static constexpr const char* CRIMINAL_JURISDICTION   = "Sala Penal — Tribunal Supremo";

    // --- DEPUTIES ---
    /* "El Defensor del Pueblo estará auxiliado por un Adjunto Primero y un
     *  Adjunto Segundo, en los que podrá delegar sus funciones y que le
     *  sustituirán por su orden, en los supuestos de imposibilidad temporal
     *  y en los de cese."
     *  Same prerogatives apply to both deputies in the performance of their functions. */
    static constexpr uint8_t DEPUTY_COUNT = 2;  // Adjunto Primero + Adjunto Segundo

    // --- HOW COMPLAINTS WORK ---
    /* Any natural or juridical person (written complaint, within 1 year of the act).
     * Service is free. The watchdog may also act ex officio.
     * After investigation: advertencia · recomendación · sugerencia to the responsible official.
     * Annual report to the Cortes. Monographic reports possible on serious/urgent matters. */
    static constexpr bool SERVICE_FREE          = true;
    static constexpr bool EX_OFFICIO_ALLOWED    = true;
    static constexpr uint8_t COMPLAINT_DEADLINE_YEARS = 1;
    static constexpr bool ANNUAL_REPORT_REQUIRED = true;

    // MNP role (since November 2009):
    // National Preventive Mechanism against Torture (Optional Protocol to UNCAT,
    // adopted New York 2002-12-18). Conducts preventive visits to all detention
    // centres; reports annually to the Cortes and to the UN Subcommittee on
    // Prevention of Torture (Geneva).
    static constexpr bool HAS_MNP_ROLE = true;

    // --- GROUNDS FOR DISMISSAL ---
    enum class CeseReason : uint8_t {
        RESIGNATION                  = 0,
        TERM_EXPIRED                 = 1,
        DEATH_OR_INCAPACITY          = 2,
        NOTORIOUS_NEGLIGENCE         = 3,
        CONVICTION_INTENTIONAL_CRIME = 4,
    };

    // --- LEGAL ACTIONS AVAILABLE ---
    // · Recurso de inconstitucionalidad (art.162.1.a CE)
    // · Recurso de amparo (art.162.1.b CE)
    // · Cannot issue binding administrative decisions — only recommends/suggests
    static constexpr bool CAN_FILE_UNCONSTITUTIONALITY = true;
    static constexpr bool CAN_FILE_AMPARO              = true;
    static constexpr bool DECISIONS_ARE_BINDING        = false;

} // namespace watchdog_service


#endif // IPC_REGISTRY_HPP
