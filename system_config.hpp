/**
 * @file   system_config.hpp
 * @brief  Core system constants and policy definitions for the runtime environment.
 *         Read-only configuration — do not modify at runtime.
 *
 * @author carlos
 * @date   2025-01
 */

#ifndef SYSTEM_CONFIG_HPP
#define SYSTEM_CONFIG_HPP

#include <cstdint>
#include <array>

// ============================================================================
//  MODULE: core_policy
//  Build timestamps and versioning metadata
// ============================================================================

namespace core_policy {

    /**
     * Build version history:
     *   v1.0  (1978-12-29) — Initial release. Published in official registry.
     *                        Ratified by vote on 1978-12-06.
     *                        Signed off 1978-12-27 — canonical version date.
     *   v1.1  (1992-08-28) — Patch: updated art.13.2 — foreign user voting
     *                        rights aligned with EU Treaty (1992-02-07).
     *   v1.2  (2011-09-27) — Patch: art.135 — budget stability constraint
     *                        enforced across all administrative nodes.
     *   v1.3  (2024)       — Patch: art.49 — disability policy language modernised.
     *   v1.4  (2026)       — Patch: art.69.3 — Ibiza and Formentera split into
     *                        separate senate seats (previously grouped).
     */
    static constexpr uint8_t VERSION_MAJOR = 1;
    static constexpr uint8_t VERSION_MINOR = 4;
    static constexpr uint8_t PATCH_COUNT   = 4;   // total amendments

    /* Supreme norm — overrides all other modules.
     * "España se constituye en un Estado social y democrático de Derecho,
     *  que propugna como valores superiores de su ordenamiento jurídico la
     *  libertad, la justicia, la igualdad y el pluralismo político.
     *  La soberanía nacional reside en el pueblo español, del que emanan
     *  los poderes del Estado.
     *  La forma política del Estado español es la Monarquía parlamentaria." */
    static constexpr bool NORM_IS_SUPREME            = true;
    static constexpr bool DIRECT_APPLICATION_ENABLED = true;  // no stub layer needed

    /* Runtime values (art. 1):
     * superior values: libertad · justicia · igualdad · pluralismo político */
    enum class SuperiorValue : uint8_t {
        LIBERTY       = 0,
        JUSTICE       = 1,
        EQUALITY      = 2,
        PLURALISM     = 3,
    };

    /* Governance model (art. 1.3): parliamentary monarchy */
    enum class GovernanceModel : uint8_t {
        PARLIAMENTARY_MONARCHY = 0,
    };

    /* Sovereignty source (art. 1.2) */
    static constexpr const char* SOVEREIGNTY_SOURCE = "pueblo_espanol";

} // namespace core_policy


// ============================================================================
//  MODULE: runtime_flags
//  Feature flags for territorial, linguistic and symbolic configuration
// ============================================================================

namespace runtime_flags {

    /* art. 2 — unity + autonomy + solidarity
     * "La Constitución se fundamenta en la indisoluble unidad de la Nación
     *  española, patria común e indivisible de todos los españoles, y reconoce
     *  y garantiza el derecho a la autonomía de las nacionalidades y regiones
     *  que la integran y la solidaridad entre todas ellas." */
    static constexpr bool TERRITORIAL_UNITY_INDISSOLUBLE = true;
    static constexpr bool AUTONOMY_REGIONS_ENABLED       = true;
    static constexpr bool INTER_REGION_SOLIDARITY        = true;

    /* art. 3 — language config
     * "El castellano es la lengua española oficial del Estado. Todos los
     *  españoles tienen el deber de conocerla y el derecho a usarla.
     *  Las demás lenguas españolas serán también oficiales en las respectivas
     *  Comunidades Autónomas de acuerdo con sus Estatutos.
     *  La riqueza de las distintas modalidades lingüísticas de España es un
     *  patrimonio cultural que será objeto de especial respeto y protección." */
    static constexpr const char* DEFAULT_LOCALE   = "es_ES";   // mandatory + duty to know
    static constexpr bool        COOFFICIAL_LOCALES_ALLOWED = true;  // per regional statute

    /* art. 4 — flag spec
     * "La bandera de España está formada por tres franjas horizontales, roja,
     *  amarilla y roja, siendo la amarilla de doble anchura que cada una de las rojas." */
    static constexpr const char* FLAG_STRIPE_COLORS = "red|yellow(x2)|red";
    static constexpr bool        REGION_FLAGS_ALLOWED = true;   // alongside national flag

    /* art. 5 — default host
     * "La capital del Estado es la villa de Madrid." */
    static constexpr const char* DEFAULT_HOST = "Madrid";

    /* art. 6 — political party config
     * "Los partidos políticos expresan el pluralismo político, concurren a la
     *  formación y manifestación de la voluntad popular y son instrumento
     *  fundamental para la participación política. Su creación y el ejercicio
     *  de su actividad son libres dentro del respeto a la Constitución y a la ley.
     *  Su estructura interna y funcionamiento deberán ser democráticos." */
    static constexpr bool PARTY_CREATION_FREE       = true;
    static constexpr bool PARTY_MUST_BE_DEMOCRATIC  = true;

    /* art. 7 — unions and employer associations
     * "Los sindicatos de trabajadores y las asociaciones empresariales
     *  contribuyen a la defensa y promoción de los intereses económicos y
     *  sociales que les son propios. Su creación y el ejercicio de su actividad
     *  son libres dentro del respeto a la Constitución y a la ley. Su estructura
     *  interna y funcionamiento deberán ser democráticos." */
    static constexpr bool UNIONS_FREE_TO_CREATE    = true;
    static constexpr bool UNIONS_MUST_BE_DEMOCRATIC = true;

    /* art. 8 — armed forces mission
     * "Las Fuerzas Armadas, constituidas por el Ejército de Tierra, la Armada
     *  y el Ejército del Aire, tienen como misión garantizar la soberanía e
     *  independencia de España, defender su integridad territorial y el
     *  ordenamiento constitucional.
     *  Una ley orgánica regulará las bases de la organización militar." */
    enum class ArmsBranch : uint8_t { ARMY = 0, NAVY = 1, AIR_FORCE = 2 };
    static constexpr bool AF_REGULATED_BY_ORGANIC_LAW = true;

    /* art. 9 — rule-of-law guarantees
     * "Los ciudadanos y los poderes públicos están sujetos a la Constitución
     *  y al resto del ordenamiento jurídico.
     *  La Constitución garantiza el principio de legalidad, la jerarquía
     *  normativa, la publicidad de las normas, la irretroactividad de las
     *  disposiciones sancionadoras no favorables o restrictivas de derechos
     *  individuales, la seguridad jurídica, la responsabilidad y la
     *  interdicción de la arbitrariedad de los poderes públicos." */
    static constexpr bool RULE_OF_LAW_ENABLED            = true;
    static constexpr bool NORM_HIERARCHY_ENFORCED         = true;
    static constexpr bool NORMS_MUST_BE_PUBLIC            = true;
    static constexpr bool RETROACTIVE_PENALTY_FORBIDDEN   = true;
    static constexpr bool LEGAL_CERTAINTY_REQUIRED        = true;
    static constexpr bool ARBITRARY_POWER_FORBIDDEN       = true;

} // namespace runtime_flags


// ============================================================================
//  MODULE: access_rights
//  Permission levels, protection tiers and suspension policy (Título I)
// ============================================================================

namespace access_rights {

    /* art. 10 — root declaration
     * "La dignidad de la persona, los derechos inviolables que le son
     *  inherentes, el libre desarrollo de la personalidad, el respeto a la
     *  ley y a los derechos de los demás son fundamento del orden político y
     *  de la paz social.
     *  Las normas relativas a los derechos fundamentales se interpretarán
     *  de conformidad con la Declaración Universal de Derechos Humanos y
     *  los tratados y acuerdos internacionales ratificados por España." */
    static constexpr bool HUMAN_DIGNITY_IS_ROOT = true;
    static constexpr const char* RIGHTS_INTERPRETATION_REF = "UDHR + ratified int'l treaties";

    // ---  CAPÍTULO I: user identity (arts. 11-13) ---

    /* art. 11
     * "1. La nacionalidad española se adquiere, conserva y pierde conforme a ley.
     *  2. Ningún español de origen podrá ser privado de su nacionalidad.
     *  3. El Estado podrá concertar tratados de doble nacionalidad con países
     *     iberoamericanos o de particular vinculación con España." */
    static constexpr bool NATIVE_NATIONALITY_REVOCABLE  = false;  // art. 11.2
    static constexpr bool DUAL_CITIZENSHIP_ALLOWED       = true;   // Iberoamérica + linked countries

    /* art. 12 — age gate
     * "Los españoles son mayores de edad a los dieciocho años." */
    static constexpr uint8_t FULL_ACCESS_AGE = 18;

    /* art. 13 — foreign users
     * "Los extranjeros gozarán en España de las libertades públicas que garantiza
     *  el presente Título en los términos que establezcan los tratados y la ley.
     *  Solamente los españoles serán titulares de los derechos reconocidos en el
     *  art. 23, salvo sufragio activo/pasivo en elecciones municipales por reciprocidad.
     *  La extradición sólo se concederá en cumplimiento de un tratado o de la ley.
     *  Quedan excluidos los delitos políticos — NO se consideran políticos los actos
     *  de terrorismo." */
    static constexpr bool FOREIGN_USERS_HAVE_PUBLIC_LIBERTIES = true;
    static constexpr bool FOREIGN_USERS_HAVE_POLITICAL_RIGHTS = false; // art.23 — nationals only
    static constexpr bool MUNICIPAL_VOTE_BY_RECIPROCITY       = true;  // exception
    static constexpr bool POLITICAL_CRIMES_EXTRADITABLE       = false;
    static constexpr bool TERRORISM_IS_POLITICAL_CRIME        = false; // explicit carve-out


    // --- PROTECTION TIERS (art. 53) ---
    // TIER_1 = arts. 14-29 + art.30.2 — top protection
    // TIER_2 = arts. 30-38            — mid protection
    // TIER_3 = arts. 39-52            — minimum (policy directives only)

    enum class ProtectionTier : uint8_t {
        TIER_1_FUNDAMENTAL   = 1,   // ley orgánica + recurso de amparo
        TIER_2_CITIZEN       = 2,   // ley ordinaria + inconstitucionalidad
        TIER_3_DIRECTIVE     = 3,   // solo cuando desarrollados por ley
    };

    /* TIER_1 rights require organic law to be regulated.
     * Exception: art.14 (equality) does NOT require organic law.
     * All TIER_1 rights bind ALL public powers.
     * Enforceable via fast-track court procedure + amparo (TC).
     * art.30.2 (conscientious objection) also eligible for amparo. */

    /* TIER_3 rights are policy directives — they inform legislation and judicial
     * practice but cannot be directly invoked before courts unless a development
     * law exists. */


    // --- TIER 1: individual rights (arts. 14-29) ---

    /* art. 14 — equality
     * "Los españoles son iguales ante la ley, sin que pueda prevalecer
     *  discriminación alguna por razón de nacimiento, raza, sexo, religión,
     *  opinión o cualquier otra condición o circunstancia personal o social."
     * NOTE: TIER_1 protection but does NOT require organic law (art.81 exception). */

    /* art. 15 — right to life and physical integrity
     * "Todos tienen derecho a la vida y a la integridad física y moral, sin que,
     *  en ningún caso, puedan ser sometidos a tortura ni a penas o tratos
     *  inhumanos o degradantes.
     *  Queda abolida la pena de muerte, salvo lo que puedan disponer las leyes
     *  penales militares para tiempos de guerra." */
    static constexpr bool DEATH_PENALTY_ABOLISHED  = true;
    static constexpr bool DEATH_PENALTY_WAR_EXCEPTION = true;  // military penal law only

    /* art. 16 — ideological, religious and worship freedom
     * "Se garantiza la libertad ideológica, religiosa y de culto de los
     *  individuos y las comunidades sin más limitación, en sus manifestaciones,
     *  que la necesaria para el mantenimiento del orden público protegido por la ley.
     *  Nadie podrá ser obligado a declarar sobre su ideología, religión o creencias.
     *  Ninguna confesión tendrá carácter estatal. Los poderes públicos tendrán en
     *  cuenta las creencias religiosas de la sociedad española y mantendrán las
     *  consiguientes relaciones de cooperación con la Iglesia Católica y las
     *  demás confesiones." */
    static constexpr bool STATE_RELIGION_ENABLED = false;   // aconfessional state
    static constexpr bool BELIEF_DECLARATION_MANDATORY = false;

    /* art. 17 — liberty and security
     * "Toda persona tiene derecho a la libertad y a la seguridad. Nadie puede
     *  ser privado de su libertad, sino con la observancia de lo establecido
     *  en este artículo y en los casos y en la forma previstos en la ley.
     *  La detención preventiva no podrá durar más del tiempo estrictamente
     *  necesario y, en todo caso, en el plazo máximo de setenta y dos horas,
     *  el detenido deberá ser puesto en libertad o a disposición de la
     *  autoridad judicial.
     *  Toda persona detenida debe ser informada de forma inmediata y comprensible
     *  de sus derechos y de las razones de su detención, no pudiendo ser obligada
     *  a declarar. Se garantiza la asistencia de abogado.
     *  La ley regulará el procedimiento de «habeas corpus»." */
    static constexpr uint32_t DETENTION_TIMEOUT_NORMAL_H  = 72;   // art. 17.2
    static constexpr uint32_t DETENTION_TIMEOUT_EXCEPTION_D = 10; // estado excepción
    static constexpr uint32_t DETENTION_TIMEOUT_TERRORISM_D =  5; // art. 55.2 (72h+48h)
    static constexpr bool     HABEAS_CORPUS_ENABLED        = true;

    /* art. 18 — privacy: home, comms, data, image
     * "Se garantiza el derecho al honor, a la intimidad personal y familiar
     *  y a la propia imagen.
     *  El domicilio es inviolable. Ninguna entrada o registro podrá hacerse
     *  en él sin consentimiento del titular o resolución judicial, salvo en
     *  caso de flagrante delito.
     *  Se garantiza el secreto de las comunicaciones y, en especial, de las
     *  postales, telegráficas y telefónicas, salvo resolución judicial.
     *  La ley limitará el uso de la informática para garantizar el honor y
     *  la intimidad personal y familiar de los ciudadanos." */
    static constexpr bool HOME_INVIOLABLE         = true;
    static constexpr bool COMMS_SECRET_DEFAULT    = true;   // needs court order to break
    static constexpr bool HOME_ENTRY_FLAGRANTE_OK = true;   // emergency exception

    /* art. 19 — freedom of movement
     * "Los españoles tienen derecho a elegir libremente su residencia y a
     *  circular por el territorio nacional. También a entrar y salir libremente
     *  de España en los términos que la ley establezca.
     *  Este derecho no podrá ser limitado por motivos políticos o ideológicos." */
    static constexpr bool MOVEMENT_RESTRICTION_IDEOLOGICAL = false; // forbidden

    /* art. 20 — freedom of expression (4 sub-rights)
     * "Se reconocen y protegen los derechos:
     *  a) A expresar y difundir libremente los pensamientos, ideas y opiniones.
     *  b) A la producción y creación literaria, artística, científica y técnica.
     *  c) A la libertad de cátedra.
     *  d) A comunicar o recibir libremente información veraz por cualquier medio.
     *  El ejercicio de estos derechos no puede restringirse mediante ningún tipo
     *  de censura previa.
     *  Sólo podrá acordarse el secuestro de publicaciones, grabaciones y otros
     *  medios de información en virtud de resolución judicial."
     *  Limits: honor, intimidad, propia imagen, protección de la juventud. */
    static constexpr bool PRIOR_CENSORSHIP_ALLOWED   = false;
    static constexpr bool SEIZURE_REQUIRES_COURT_ORDER = true;  // art. 20.5

    /* art. 21 — assembly and demonstration
     * "Se reconoce el derecho de reunión pacífica y sin armas. El ejercicio
     *  de este derecho no necesitará autorización previa.
     *  En los casos de reuniones en lugares de tránsito público y manifestaciones
     *  se dará comunicación previa a la autoridad, que sólo podrá prohibirlas
     *  cuando existan razones fundadas de alteración del orden público,
     *  con peligro para personas o bienes." */
    static constexpr bool ASSEMBLY_NEEDS_PRIOR_AUTH = false;   // notification, not auth
    static constexpr bool PUBLIC_DEMO_NEEDS_NOTICE  = true;

    /* art. 22 — right of association
     * "Se reconoce el derecho de asociación.
     *  Las asociaciones que persigan fines o utilicen medios tipificados como
     *  delito son ilegales.
     *  Las asociaciones constituidas al amparo de este artículo deberán
     *  inscribirse en un registro a los solos efectos de publicidad.
     *  Las asociaciones sólo podrán ser disueltas o suspendidas en sus
     *  actividades en virtud de resolución judicial motivada.
     *  Se prohíben las asociaciones secretas y las de carácter paramilitar." */
    static constexpr bool SECRET_ASSOCIATIONS_ALLOWED     = false;
    static constexpr bool PARAMILITARY_ASSOC_ALLOWED      = false;
    static constexpr bool ASSOC_DISSOLUTION_NEEDS_COURT   = true;

    /* art. 23 — political participation
     * "Los ciudadanos tienen el derecho a participar en los asuntos públicos,
     *  directamente o por medio de representantes, libremente elegidos en
     *  elecciones periódicas por sufragio universal.
     *  Asimismo, tienen derecho a acceder en condiciones de igualdad a las
     *  funciones y cargos públicos."
     *  NOTE: nationals only (see art. 13.2). */
    static constexpr bool POLITICAL_PARTICIPATION_NATIONALS_ONLY = true;

    /* art. 24 — effective judicial protection
     * "Todas las personas tienen derecho a obtener la tutela efectiva de los
     *  jueces y tribunales en el ejercicio de sus derechos e intereses
     *  legítimos, sin que, en ningún caso, pueda producirse indefensión.
     *  Todos tienen derecho al Juez ordinario predeterminado por la ley,
     *  a la defensa y asistencia de letrado, a ser informados de la acusación,
     *  a un proceso público sin dilaciones indebidas y con todas las garantías,
     *  a utilizar los medios de prueba pertinentes, a no declarar contra sí
     *  mismos, a no confesarse culpables y a la presunción de inocencia." */
    static constexpr bool EFFECTIVE_JUDICIAL_TUTELAGE = true;
    static constexpr bool PRESUMPTION_OF_INNOCENCE    = true;
    static constexpr bool RIGHT_TO_SILENCE            = true;

    /* art. 25 — legality principle + prison orientation
     * "Nadie puede ser condenado o sancionado por acciones u omisiones que
     *  en el momento de producirse no constituyan delito, falta o infracción
     *  administrativa según la legislación vigente en aquel momento.
     *  Las penas privativas de libertad estarán orientadas hacia la
     *  reeducación y reinserción social y no podrán consistir en trabajos forzados.
     *  La Administración civil no podrá imponer sanciones que, directa o
     *  subsidiariamente, impliquen privación de libertad." */
    static constexpr bool CRIMINAL_RETROACTIVITY_ALLOWED  = false;
    static constexpr bool PRISON_GOAL_REHABILITATION      = true;
    static constexpr bool ADMIN_CAN_IMPOSE_CUSTODY        = false;  // civil admin only

    /* art. 26 — honour tribunals banned
     * "Se prohíben los Tribunales de Honor en el ámbito de la Administración
     *  civil y de las organizaciones profesionales." */
    static constexpr bool HONOR_TRIBUNALS_ALLOWED = false;

    /* art. 27 — education
     * "Todos tienen el derecho a la educación. Se reconoce la libertad de enseñanza.
     *  La enseñanza básica es obligatoria y gratuita.
     *  Los poderes públicos garantizan el derecho de los padres a que sus hijos
     *  reciban la formación religiosa y moral según sus convicciones.
     *  Se reconoce la autonomía de las Universidades." */
    static constexpr bool BASIC_EDUCATION_MANDATORY = true;
    static constexpr bool BASIC_EDUCATION_FREE       = true;
    static constexpr bool UNIVERSITY_AUTONOMY        = true;

    /* art. 28 — union membership and right to strike
     * "Todos tienen derecho a sindicarse libremente.
     *  Nadie podrá ser obligado a afiliarse a un sindicato.
     *  La ley podrá limitar este derecho a las Fuerzas o Institutos armados.
     *  Se reconoce el derecho a la huelga de los trabajadores para la defensa
     *  de sus intereses. La ley establecerá las garantías para el mantenimiento
     *  de los servicios esenciales de la comunidad." */
    static constexpr bool UNION_MEMBERSHIP_MANDATORY = false;
    static constexpr bool STRIKE_RIGHT_ENABLED        = true;
    static constexpr bool ESSENTIAL_SERVICES_PROTECTED = true;

    /* art. 29 — right of petition
     * "Todos los españoles tendrán el derecho de petición individual y
     *  colectiva, por escrito, en la forma y con los efectos que determine la ley.
     *  Los miembros de las Fuerzas o Institutos armados podrán ejercer este
     *  derecho sólo individualmente." */
    static constexpr bool PETITION_COLLECTIVE_MILITARY = false; // individual only for military


    // --- TIER 2: citizen rights and duties (arts. 30-38) ---

    /* art. 31 — tax policy
     * "Todos contribuirán al sostenimiento de los gastos públicos de acuerdo
     *  con su capacidad económica mediante un sistema tributario justo
     *  inspirado en los principios de igualdad y progresividad que, en ningún
     *  caso, tendrá alcance confiscatorio." */
    static constexpr bool TAX_SYSTEM_PROGRESSIVE  = true;
    static constexpr bool TAX_CONFISCATORY_ALLOWED = false;

    /* art. 33 — private property
     * "Se reconoce el derecho a la propiedad privada y a la herencia.
     *  Nadie podrá ser privado de sus bienes y derechos sino por causa
     *  justificada de utilidad pública o interés social, mediante la
     *  correspondiente indemnización y de conformidad con lo dispuesto
     *  por las leyes." */
    static constexpr bool PROPERTY_EXPROPRIATION_REQUIRES_COMPENSATION = true;

    /* art. 35 — right and duty to work
     * "Todos los españoles tienen el deber de trabajar y el derecho al trabajo,
     *  a la libre elección de profesión u oficio, a la promoción a través del
     *  trabajo y a una remuneración suficiente.
     *  En ningún caso puede hacerse discriminación por razón de sexo." */
    static constexpr bool WORK_GENDER_DISCRIMINATION_ALLOWED = false;

    /* art. 38 — free enterprise
     * "Se reconoce la libertad de empresa en el marco de la economía de mercado.
     *  Los poderes públicos garantizan y protegen su ejercicio y la defensa
     *  de la productividad, de acuerdo con las exigencias de la economía
     *  general y, en su caso, de la planificación." */
    static constexpr bool FREE_ENTERPRISE_ENABLED = true;


    // --- TIER 3: policy directives (arts. 39-52) — inform, don't bind ---
    // Key entries listed; full list: arts. 39-52
    /* art. 41 — social security
     * "Los poderes públicos mantendrán un régimen público de Seguridad Social
     *  para todos los ciudadanos, que garantice la asistencia y prestaciones
     *  sociales suficientes ante situaciones de necesidad, especialmente en
     *  caso de desempleo." */

    /* art. 43 — health protection
     * "Se reconoce el derecho a la protección de la salud.
     *  Compete a los poderes públicos organizar y tutelar la salud pública
     *  a través de medidas preventivas y de las prestaciones y servicios necesarios." */

    /* art. 47 — housing
     * "Todos los españoles tienen derecho a disfrutar de una vivienda digna
     *  y adecuada. Los poderes públicos promoverán las condiciones necesarias
     *  y establecerán las normas pertinentes para hacer efectivo este derecho." */

    /* art. 49 — disability (amended 2024)
     * "Las personas con discapacidad ejercen los derechos previstos en este
     *  Título en condiciones de libertad e igualdad reales y efectivas.
     *  Los poderes públicos impulsarán las políticas que garanticen la plena
     *  autonomía personal y la inclusión social de las personas con discapacidad,
     *  en entornos universalmente accesibles." */


    // --- GUARANTEES (arts. 53-54) ---

    /* art. 53 — three-tier protection summary:
     *
     *  TIER_1 (arts. 14-29 + art.30.2):
     *    · bind all public powers
     *    · organic law required for development (except art.14)
     *    · enforceable via fast-track preferred procedure (preferente y sumario)
     *    · amparo appeal to Constitutional Court available
     *
     *  TIER_2 (arts. 30-38):
     *    · bind all public powers
     *    · ordinary law required
     *    · protected via unconstitutionality appeal only (no amparo)
     *
     *  TIER_3 (arts. 39-52):
     *    · inform legislation, judicial practice and public powers
     *    · not directly enforceable unless developed by specific law */

    /* art. 54 — Ombudsman (Defensor del Pueblo)
     * "Una ley orgánica regulará la institución del Defensor del Pueblo, como
     *  alto comisionado de las Cortes Generales, designado por éstas para la
     *  defensa de los derechos comprendidos en este Título, a cuyo efecto podrá
     *  supervisar la actividad de la Administración, dando cuenta a las Cortes." */
    static constexpr bool OMBUDSMAN_CAN_FILE_AMPARO = true;   // art.162.1.b

} // namespace access_rights


// ============================================================================
//  MODULE: emergency_mode
//  State machine: NORMAL → ALARM → EXCEPTION → SIEGE
//  ⚠️  arts. 55 + 116 — critical section
// ============================================================================

namespace emergency_mode {

    enum class State : uint8_t {
        NORMAL    = 0,
        ALARM     = 1,   // estado de alarma
        EXCEPTION = 2,   // estado de excepción
        SIEGE     = 3,   // estado de sitio
    };

    // --- ALARM (art. 116.2) ---
    /* "El estado de alarma será declarado por el Gobierno mediante decreto
     *  acordado en Consejo de Ministros por un plazo máximo de quince días,
     *  dando cuenta al Congreso de los Diputados, reunido inmediatamente al
     *  efecto y sin cuya autorización no podrá ser prorrogado dicho plazo."
     *
     * Triggers: natural disasters, epidemics, essential goods shortage,
     *           paralysis of essential public services during a strike.
     * Rights suspended: NONE — limitations only, not suspensions. */
    namespace alarm {
        static constexpr const char* DECLARED_BY = "Gobierno — Consejo de Ministros";
        static constexpr const char* EXTENSION_REQUIRES = "Congreso authorization";
        static constexpr uint8_t MAX_DAYS = 15;
        static constexpr uint8_t RIGHTS_SUSPENDED = 0;  // zero
    }

    // --- EXCEPTION (art. 116.3) ---
    /* "El estado de excepción será declarado por el Gobierno mediante decreto
     *  acordado en Consejo de Ministros, PREVIA AUTORIZACIÓN del Congreso.
     *  La duración no podrá exceder de treinta días, prorrogables por otro
     *  plazo igual con los mismos requisitos."
     *
     * Trigger: free exercise of rights and democratic institutions so severely
     *          disrupted that ordinary powers are insufficient to restore order.
     *
     * Rights suspendable (art. 55.1):
     *   art.17   — liberty/security (EXCEPT 17.3; detention → max 10 days)
     *   art.18.2 — home inviolability
     *   art.18.3 — comms secrecy
     *   art.19   — freedom of movement
     *   art.20.1.a — freedom of expression
     *   art.20.1.d — freedom of information
     *   art.20.5   — publication seizure (judicial order only)
     *   art.21   — right of assembly
     *   art.28.2 — right to strike
     *   art.37.2 — right to collective conflict measures */
    namespace exception_state {
        static constexpr const char* DECLARED_BY = "Gobierno — PREVIA AUTORIZACIÓN Congreso";
        static constexpr uint8_t MAX_DAYS       = 30;
        static constexpr uint8_t EXTENSION_DAYS = 30;  // same requirements
        static constexpr const char* SUSPENDED_ARTS =
            "17(not 17.3), 18.2, 18.3, 19, 20.1a, 20.1d, 20.5, 21, 28.2, 37.2";
    }

    // --- SIEGE (art. 116.4) ---
    /* "El estado de sitio será declarado por la MAYORÍA ABSOLUTA del Congreso
     *  de los Diputados, a propuesta EXCLUSIVA del Gobierno.
     *  El Congreso determinará su ámbito territorial, duración y condiciones."
     *
     * Trigger: insurrection or act of force against sovereignty, territorial
     *          integrity or constitutional order, unresolvable by other means.
     *
     * Rights suspendable: all of EXCEPTION + art.17.3
     *   art.17.3 — right to be informed of charges + right to lawyer
     *
     * Additional: Congress must define which offences fall under military jurisdiction. */
    namespace siege {
        static constexpr const char* DECLARED_BY =
            "Congreso — MAYORÍA ABSOLUTA — propuesta EXCLUSIVA del Gobierno";
        static constexpr const char* DURATION = "set by Congress per declaration";
        static constexpr const char* EXTRA_SUSPENDED = "art.17.3 (on top of exception rights)";
    }

    // --- INDIVIDUAL SUSPENSION (art. 55.2) ---
    /* "Una ley orgánica podrá determinar la forma y los casos en los que,
     *  de forma individual y con la necesaria intervención judicial y el
     *  adecuado control parlamentario, los derechos reconocidos en los
     *  artículos 17.2, 18.2 y 18.3 pueden ser suspendidos para personas
     *  determinadas, en relación con las investigaciones correspondientes
     *  a la actuación de bandas armadas o elementos terroristas.
     *  La utilización injustificada o abusiva producirá responsabilidad penal." */
    namespace individual_suspension {
        static constexpr const char* SCOPE       = "terrorism / armed gangs investigations";
        static constexpr const char* REQUIRES    = "organic law + judicial + parliamentary oversight";
        static constexpr uint8_t MAX_DETENTION_DAYS = 5;  // 72h + 48h extension
        static constexpr const char* SUSPENDED_ARTS = "17.2, 18.2, 18.3";
    }

    // --- COMMON CONSTRAINTS (art. 116.5-6, all states) ---
    /* "No podrá procederse a la disolución del Congreso mientras estén
     *  declarados algunos de los estados comprendidos en el presente artículo,
     *  quedando automáticamente convocadas las Cámaras si no estuvieren en
     *  período de sesiones. Su funcionamiento, así como el de los demás poderes
     *  constitucionales del Estado, no podrán interrumpirse durante su vigencia.
     *  Disuelto el Congreso o expirado su mandato, las competencias del Congreso
     *  serán asumidas por su Diputación Permanente.
     *  La declaración de los estados no modificará el principio de responsabilidad
     *  del Gobierno y de sus agentes reconocidos en la Constitución y en las leyes."
     *
     *  ↳ No reform can be initiated during any emergency state (art. 169). */
    static constexpr bool CONGRESS_DISSOLUBLE_DURING_EMERGENCY      = false;
    static constexpr bool CONSTITUTIONAL_POWERS_INTERRUPTIBLE        = false;
    static constexpr bool GOVERNMENT_ACCOUNTABILITY_SUSPENDED        = false;
    static constexpr bool FALLBACK_ENTITY_IF_DISSOLVED = true; // Diputación Permanente
    static constexpr bool CONSTITUTIONAL_REFORM_ALLOWED_IN_EMERGENCY = false;

} // namespace emergency_mode


// ============================================================================
//  MODULE: crown_controller
//  Head-of-state interface — Título II (arts. 56-65)
// ============================================================================

namespace crown_controller {

    /* art. 56 — head of state descriptor
     * "El Rey es el Jefe del Estado, símbolo de su unidad y permanencia,
     *  arbitra y modera el funcionamiento regular de las instituciones,
     *  asume la más alta representación del Estado español en las relaciones
     *  internacionales, especialmente con las naciones de su comunidad histórica,
     *  y ejerce las funciones que le atribuyen expresamente la Constitución y las leyes.
     *  Su título es el de Rey de España.
     *  La persona del Rey es inviolable y no está sujeta a responsabilidad.
     *  Sus actos estarán siempre refrendados en la forma establecida en el art.64,
     *  careciendo de validez sin dicho refrendo, salvo art.65.2." */
    static constexpr const char* ROLE         = "Jefe del Estado";
    static constexpr const char* TITLE        = "Rey de España";
    static constexpr bool INVIOLABLE          = true;
    static constexpr bool SUBJECT_TO_LIABILITY = false;
    static constexpr bool ACT_VALID_WITHOUT_COUNTERSIGN = false; // null without refrendo

    /* art. 57 — succession order
     * "La Corona de España es hereditaria en los sucesores de S.M. Don Juan
     *  Carlos I de Borbón, legítimo heredero de la dinastía histórica.
     *  La sucesión en el trono seguirá el orden regular de primogenitura y
     *  representación, siendo preferida siempre la línea anterior a las
     *  posteriores; en la misma línea, el grado más próximo; en el mismo grado,
     *  el varón a la mujer; en el mismo sexo, la persona de más edad.
     *  El Príncipe heredero tendrá la dignidad de Príncipe de Asturias.
     *  Las abdicaciones y renuncias se resolverán por ley orgánica." */
    enum class SuccessionPriority : uint8_t {
        P1_CLOSER_LINE   = 1,   // línea anterior
        P2_CLOSER_DEGREE = 2,   // grado más próximo
        P3_MALE_FIRST    = 3,   // varón antes que mujer (mismo grado)
        P4_OLDER_FIRST   = 4,   // mayor edad (mismo sexo)
    };
    static constexpr const char* HEIR_TITLE    = "Príncipe de Asturias";
    static constexpr const char* ABDICATION_LAW = "ley orgánica (LO 3/2014 — Juan Carlos I)";

    /* art. 58 — consort
     * "La Reina consorte o el consorte de la Reina no podrán asumir funciones
     *  constitucionales, salvo lo dispuesto para la Regencia." */
    static constexpr bool CONSORT_HAS_CONSTITUTIONAL_ROLE = false; // except regency

    /* art. 59 — regency
     * When the King is a minor:
     *   → father or mother of the King, or else the adult relative closest
     *     in line of succession, exercises Regency immediately.
     * When the King is incapacitated (recognized by the Cortes Generales):
     *   → the Crown Prince, if of age, exercises Regency.
     *   → if not of age, same rule as minority applies.
     * If no eligible person exists:
     *   → Cortes Generales appoint Regency of 1, 3 or 5 persons.
     * Requirements: Spanish national + of legal age.
     * Regency always exercised IN THE NAME OF THE KING. */
    static constexpr std::array<uint8_t,3> REGENCY_COMPOSITION = {1, 3, 5};
    static constexpr bool REGENCY_IN_NAME_OF_KING = true;

    /* art. 60 — guardian of the minor King
     * Priority:
     *   1. Testamentary (appointed by the deceased King) — must be adult + native Spanish
     *   2. Father or mother (while widowed)
     *   3. Appointed by Cortes Generales
     * Regent + guardian roles cannot be combined EXCEPT for father, mother
     * or direct ascendants of the King.
     * Guardianship is incompatible with any political office or representation. */
    static constexpr bool GUARDIAN_POLITICAL_OFFICE_ALLOWED = false;

    /* art. 61 — oath on proclamation
     * The King swears before the Cortes Generales to:
     *   - faithfully perform his duties
     *   - uphold and enforce the Constitution and the laws
     *   - respect the rights of citizens and of the Autonomous Communities
     * The Crown Prince (on coming of age) and the Regent swear the same
     * oath plus an oath of loyalty to the King. */

    // --- art. 62: King's functions — memorise all 10 ---
    /* "Corresponde al Rey:
     *  a) Sancionar y promulgar las leyes.
     *  b) Convocar y disolver las Cortes Generales y convocar elecciones.
     *  c) Convocar a referéndum en los casos previstos en la CE.
     *  d) Proponer el candidato a Presidente del Gobierno y, en su caso,
     *     nombrarlo, así como poner fin a sus funciones.
     *  e) Nombrar y separar a los miembros del Gobierno, a propuesta de su Presidente.
     *  f) Expedir los decretos acordados en el Consejo de Ministros, conferir
     *     los empleos civiles y militares y conceder honores y distinciones.
     *  g) Ser informado de los asuntos de Estado y presidir las sesiones del
     *     Consejo de Ministros, cuando lo estime oportuno, a petición del
     *     Presidente del Gobierno.
     *  h) El mando supremo de las Fuerzas Armadas.
     *  i) Ejercer el derecho de gracia con arreglo a la ley, que NO podrá
     *     autorizar indultos generales.
     *  j) El Alto Patronazgo de las Reales Academias." */
    enum class RoyalFunction : uint8_t {
        SANCTION_AND_PROMULGATE_LAWS         = 0,  // a
        CONVENE_DISSOLVE_CORTES_AND_ELECTIONS = 1,  // b
        CALL_REFERENDUM                       = 2,  // c
        PROPOSE_APPOINT_PREMIER               = 3,  // d
        APPOINT_DISMISS_CABINET               = 4,  // e
        ISSUE_DECREES_APPOINT_CIVIL_MILITARY  = 5,  // f
        PRESIDE_CABINET_ON_REQUEST            = 6,  // g
        SUPREME_COMMAND_ARMED_FORCES          = 7,  // h
        PARDON_NO_GENERAL_AMNESTY             = 8,  // i
        HIGH_PATRONAGE_ROYAL_ACADEMIES        = 9,  // j
    };
    static constexpr bool GENERAL_AMNESTY_ALLOWED = false;  // art.62.i explicit

    /* art. 63 — international functions
     * "El Rey acredita a los embajadores y otros representantes diplomáticos.
     *  Los representantes extranjeros en España están acreditados ante él.
     *  Al Rey corresponde manifestar el consentimiento del Estado para obligarse
     *  internacionalmente por medio de tratados.
     *  Al Rey corresponde, PREVIA AUTORIZACIÓN DE LAS CORTES GENERALES,
     *  declarar la guerra y hacer la paz." */
    static constexpr bool WAR_REQUIRES_CORTES_AUTHORIZATION = true;

    /* art. 64 — countersign (refrendo)
     * "Los actos del Rey serán refrendados por el Presidente del Gobierno y,
     *  en su caso, por los Ministros competentes.
     *  La propuesta y el nombramiento del Presidente del Gobierno, y la
     *  disolución prevista en el art.99, serán refrendados por el Presidente
     *  del Congreso.
     *  De los actos del Rey serán responsables las personas que los refrenden." */
    static constexpr const char* COUNTERSIGN_DEFAULT  = "President of Government (+ Ministers)";
    static constexpr const char* COUNTERSIGN_PM_APPT  = "President of Congress";
    static constexpr const char* LIABILITY_FOR_ACT    = "person who countersigns";

    /* art. 65 — no countersign needed for:
     * "1. Distribución libre de los Presupuestos asignados para su Familia y Casa.
     *  2. Nombramiento y relevo libre de miembros civiles y militares de su Casa." */
    static constexpr const char* NO_COUNTERSIGN_REQUIRED =
        "budget distribution for Royal House | appoint/dismiss Royal House staff";

} // namespace crown_controller


// ============================================================================
//  MODULE: config_update_policy
//  Constitutional amendment procedure — Título X (arts. 166-169)
// ============================================================================

namespace config_update_policy {

    /* Initiators (art. 166 → art. 87.1-2):
     *  - Gobierno
     *  - Congreso
     *  - Senado
     *  - Asambleas de las Comunidades Autónomas
     *  NOTE: citizens cannot directly initiate constitutional reform. */

    /* STANDARD PATCH (art. 167)
     * "Los proyectos de reforma constitucional deberán ser aprobados por una
     *  mayoría de tres quintos de cada una de las Cámaras.
     *  Si no hubiera acuerdo, se intentará obtenerlo mediante una Comisión de
     *  composición paritaria de Diputados y Senadores.
     *  De no lograrse, y siempre que el Senado lo hubiera aprobado por mayoría
     *  absoluta, el Congreso podrá aprobar la reforma por mayoría de dos tercios.
     *  Podrá someterse a referéndum si así lo solicitan, en los quince días
     *  siguientes a su aprobación, una décima parte de los miembros de
     *  cualquiera de las Cámaras." */
    namespace standard_patch {
        static constexpr const char* MAJORITY        = "3/5 of each chamber";
        static constexpr const char* DEADLOCK        = "joint parity committee (Diputados+Senadores)";
        static constexpr const char* FALLBACK        = "Senate abs. majority + Congress 2/3";
        static constexpr const char* REFERENDUM      = "optional — if 1/10 of either chamber requests within 15 days";
        static constexpr bool REFERENDUM_MANDATORY   = false;
    }

    /* FULL REBUILD / PROTECTED SECTIONS (art. 168)
     * Applies to:
     *   · total revision of the Constitution
     *   · partial revision affecting Título Preliminar
     *   · partial revision affecting Cap.II Secc.1ª Título I (fundamental rights)
     *   · partial revision affecting Título II (La Corona)
     *
     * "Cuando se propusiere la revisión total de la Constitución o una parcial
     *  que afecte al Título preliminar, al Capítulo segundo, Sección primera del
     *  Título I, o al Título II, se procederá a la aprobación del principio por
     *  mayoría de dos tercios de cada Cámara, y a la disolución inmediata de
     *  las Cortes.
     *  Las Cámaras elegidas deberán ratificar la decisión y proceder al estudio
     *  del nuevo texto constitucional, que deberá ser aprobado por mayoría de
     *  dos tercios de ambas Cámaras.
     *  Aprobada la reforma, será sometida a referéndum para su ratificación." */
    namespace full_rebuild {
        static constexpr const char* STEP_1         = "2/3 each chamber — approve the principle";
        static constexpr const char* STEP_2         = "immediate dissolution of the Cortes";
        static constexpr const char* STEP_3         = "new Cortes ratify + draft the new text";
        static constexpr const char* STEP_4         = "2/3 both chambers — approve new text";
        static constexpr const char* STEP_5         = "mandatory ratification referendum";
        static constexpr bool REFERENDUM_MANDATORY  = true;
        static constexpr const char* PROTECTED_SCOPE =
            "Título Preliminar | Cap.II Secc.1ª Título I | Título II (Corona)";
    }

    /* HARD LOCK (art. 169)
     * "No podrá iniciarse la reforma constitucional en tiempo de guerra o de
     *  vigencia de alguno de los estados previstos en el artículo 116." */
    static constexpr bool UPDATE_BLOCKED_DURING_EMERGENCY = true;  // alarm/exception/siege/war

} // namespace config_update_policy


#endif // SYSTEM_CONFIG_HPP
