/**
 * @file   process_manager.hpp
 * @brief  Process lifecycle management — scheduler policy, privilege escalation,
 *         inter-process signalling and watchdog integration.
 *
 * @author carlos
 * @date   2025-01
 *
 * @ref    CE78 Títulos IV y V (arts. 97-116) | Ley 50/1997, de 27 de noviembre
 */

#ifndef PROCESS_MANAGER_HPP
#define PROCESS_MANAGER_HPP

#include <cstdint>
#include <array>

// ============================================================================
//  MODULE: executive_process
//  Root process descriptor — Título IV CE (arts. 97-107) + Ley 50/1997
// ============================================================================

namespace executive_process {

    /* art. 97 — process mandate
     * "El Gobierno dirige la política interior y exterior, la Administración
     *  civil y militar y la defensa del Estado. Ejerce la función ejecutiva
     *  y la potestad reglamentaria de acuerdo con la Constitución y las leyes." */
    static constexpr const char* MANDATE =
        "política interior/exterior · Admin. civil y militar · defensa del Estado";
    static constexpr bool HAS_EXECUTIVE_FUNCTION   = true;
    static constexpr bool HAS_REGULATORY_POWER     = true;

    /* art. 98 — process composition
     * "1. El Gobierno se compone del Presidente, de los Vicepresidentes, en su
     *    caso, de los Ministros y de los demás miembros que establezca la ley.
     *  2. El Presidente dirige la acción del Gobierno y coordina las funciones
     *    de los demás miembros del mismo, sin perjuicio de la competencia y
     *    responsabilidad directa de éstos en su gestión.
     *  3. Los miembros del Gobierno no podrán ejercer otras funciones
     *    representativas que las propias del mandato parlamentario, ni cualquier
     *    otra función pública que no derive de su cargo, ni actividad profesional
     *    o mercantil alguna.
     *  4. La ley regulará el estatuto e incompatibilidades de los miembros del
     *    Gobierno."  → Ley 50/1997, de 27 de noviembre, del Gobierno */
    enum class Member : uint8_t {
        PRESIDENT        = 0,   // mandatory — heads and coordinates
        VICE_PRESIDENT   = 1,   // optional ("en su caso") — 0, 1 or many
        MINISTER         = 2,   // mandatory
        OTHER_BY_LAW     = 3,   // any additional members the law establishes
    };

    // Membership requirements (Ley 50/1997):
    // · Spanish national
    // · Legal age (≥ 18)
    // · Full active/passive voting rights
    // · Not barred from public office by firm judicial sentence

    // The King may preside the Cabinet to be informed about state affairs
    // (art. 62.g CE), but is NOT a member and cannot vote.
    // State Secretaries may attend but only to report on their remit.
    static constexpr bool KING_IS_CABINET_MEMBER = false;
    static constexpr bool STATE_SECRETARY_IS_CABINET_MEMBER = false;

    /* art. 103 — public administration principles
     * "1. La Administración Pública sirve con objetividad los intereses
     *    generales y actúa de acuerdo con los principios de eficacia,
     *    jerarquía, descentralización, desconcentración y coordinación,
     *    con sometimiento pleno a la ley y al Derecho.
     *  2. Los órganos de la Administración del Estado son creados, regidos y
     *    coordinados de acuerdo con la ley.
     *  3. La ley regulará el estatuto de los funcionarios públicos, el acceso
     *    a la función pública de acuerdo con los principios de mérito y
     *    capacidad..." */
    enum class AdminPrinciple : uint8_t {
        EFFECTIVENESS       = 0,
        HIERARCHY           = 1,
        DECENTRALISATION    = 2,
        DECONCENTRATION     = 3,
        COORDINATION        = 4,
    };
    static constexpr const char* CIVIL_SERVICE_ACCESS = "mérito y capacidad";

    /* art. 104 — security forces
     * "1. Las Fuerzas y Cuerpos de seguridad, bajo la dependencia del Gobierno,
     *    tendrán como misión proteger el libre ejercicio de los derechos y
     *    libertades y garantizar la seguridad ciudadana.
     *  2. Una ley orgánica determinará las funciones, principios básicos de
     *    actuación y estatutos de las Fuerzas y Cuerpos de seguridad." */
    static constexpr const char* SECURITY_FORCES_MISSION =
        "proteger derechos y libertades + garantizar seguridad ciudadana";
    static constexpr const char* SECURITY_FORCES_LAW = "ley orgánica";

    /* art. 105 — citizen interface
     * "La ley regulará:
     *  a) La audiencia de los ciudadanos en el procedimiento de elaboración
     *     de las disposiciones administrativas que les afecten.
     *  b) El acceso de los ciudadanos a los archivos y registros administrativos,
     *     salvo en lo que afecte a la seguridad y defensa del Estado, la
     *     averiguación de los delitos y la intimidad de las personas.
     *  c) El procedimiento a través del cual deben producirse los actos
     *     administrativos garantizando, cuando proceda, la audiencia del
     *     interesado." */

    /* art. 106 — judicial review of admin acts
     * "1. Los Tribunales controlan la potestad reglamentaria y la legalidad
     *    de la actuación administrativa.
     *  2. Los particulares tendrán derecho a ser indemnizados por toda lesión
     *    que sufran en cualquiera de sus bienes y derechos, salvo fuerza mayor,
     *    siempre que la lesión sea consecuencia del funcionamiento de los
     *    servicios públicos." */
    static constexpr bool ADMIN_ACTS_JUDICIALLY_REVIEWABLE = true;
    static constexpr bool PUBLIC_LIABILITY_EXCLUDES_FORCE_MAJEURE = true;

    /* art. 107 — advisory layer
     * "El Consejo de Estado es el supremo órgano consultivo del Gobierno.
     *  Una ley orgánica regulará su composición y competencia." */
    static constexpr const char* SUPREME_ADVISORY_BODY = "Consejo de Estado";


    // -----------------------------------------------------------------------
    //  SUBMODULE: root_thread — El Presidente del Gobierno
    // -----------------------------------------------------------------------

    namespace root_thread {

        /* art. 98.2 — role
         * "El Presidente dirige la acción del Gobierno y coordina las funciones
         *  de los demás miembros del mismo, sin perjuicio de la competencia y
         *  responsabilidad directa de éstos en su gestión." */
        static constexpr const char* ROLE = "Jefe del Gobierno — no mero primus inter pares";

        /* Ley 50/1997 — President's functions (enumerated):
         *  a) Represent the Government.
         *  b) Set the government programme; determine domestic/foreign policy guidelines.
         *  c) Propose to the King, after Cabinet deliberation, dissolution of Congress,
         *     Senate or the Cortes Generales.
         *  d) Raise the question of confidence (cuestión de confianza) before Congress,
         *     after Cabinet deliberation.
         *  e) Propose to the King a consultative referendum, after Congress authorisation.
         *  f) Direct defence policy; exercise functions over the Armed Forces.
         *  g) Convene, chair and set the agenda of Cabinet, without prejudice to art.62.g CE.
         *  h) Countersign, where appropriate, the King's acts; submit laws for royal assent.
         *  i) File the unconstitutionality appeal (recurso de inconstitucionalidad).
         *  j) Create, modify and abolish ministerial departments and State Secretariats
         *     by Royal Decree.
         *  k) Propose to the King the appointment and removal of Vice-Presidents and Ministers.
         *  l) Resolve attribution conflicts between different Ministries.
         *  m) Issue instructions to other Government members.
         *  n) Exercise any other powers conferred by the CE or laws. */
        enum class Function : uint8_t {
            REPRESENT_GOVERNMENT          = 0,   // a
            SET_POLICY_PROGRAMME          = 1,   // b
            PROPOSE_DISSOLUTION_OF_CORTES = 2,   // c
            RAISE_CONFIDENCE_VOTE         = 3,   // d
            PROPOSE_REFERENDUM            = 4,   // e
            DIRECT_DEFENCE_POLICY         = 5,   // f
            CONVENE_CHAIR_CABINET         = 6,   // g
            COUNTERSIGN_ROYAL_ACTS        = 7,   // h
            FILE_UNCONSTITUTIONALITY      = 8,   // i
            CREATE_MODIFY_MINISTRIES      = 9,   // j
            PROPOSE_APPOINT_REMOVE_CABINET = 10, // k
            RESOLVE_INTER_MINISTRY_CONFLICT = 11, // l
            ISSUE_INSTRUCTIONS_TO_CABINET = 12,  // m
        };

        // Substitution order (vacancy / absence / illness):
        // 1. Vice-Presidents in order of precedence
        // 2. Ministers in order of ministerial department precedence
        static constexpr const char* SUBSTITUTION_ORDER =
            "Vicepresidentes (orden prelación) → Ministros (orden departamentos)";

        // Criminal liability: Sala de lo Penal — Tribunal Supremo (art. 102)
        // Civil/patrimonial liability: Sala de lo Civil — Tribunal Supremo (LO 6/1985)
        // Political liability: solidaria ante el Congreso (art. 108)
        static constexpr const char* CRIMINAL_JURISDICTION = "Sala Penal — TS";
        static constexpr const char* CIVIL_JURISDICTION    = "Sala Civil — TS";

        /* art. 102 — special prosecution rule for treason/state security offences
         * "Si la acusación fuere por traición o por cualquier delito contra la
         *  seguridad del Estado en el ejercicio de sus funciones, sólo podrá
         *  ser planteada por iniciativa de la cuarta parte de los miembros del
         *  Congreso, y con la aprobación de la mayoría absoluta del mismo.
         *  La prerrogativa real de gracia no será aplicable a ninguno de los
         *  supuestos del presente artículo." */
        static constexpr float TREASON_INITIATIVE_FRACTION = 0.25f; // 1/4 of Congress
        static constexpr const char* TREASON_APPROVAL      = "mayoría absoluta del Congreso";
        static constexpr bool ROYAL_PARDON_APPLICABLE      = false;  // art. 102.3

    } // namespace root_thread


    // -----------------------------------------------------------------------
    //  SUBMODULE: deputy_threads — Vicepresidentes
    // -----------------------------------------------------------------------

    namespace deputy_threads {

        /* art. 98 + Ley 50/1997
         * Optional organ ("en su caso") — 0, 1 or more.
         * Functions: those assigned by the President.
         * A VP who also heads a Ministry also holds the title of Minister.
         * Appointment/removal: by the King, at the President's proposal (art.100).
         * Oath: before the King — same as President + secrecy of Cabinet deliberations
         *       (Real Decreto 707/1979). */
        static constexpr bool MANDATORY       = false;  // "en su caso"
        static constexpr const char* APPOINTED_BY = "Rey — a propuesta del Presidente (art.100)";

        // VP chairs the Comisión General de Secretarios de Estado y Subsecretarios
        // (or, failing VP, the Minister of the Presidency)
        static constexpr const char* CHAIRS_PREP_COMMITTEE =
            "Comisión General de Secretarios de Estado y Subsecretarios";

    } // namespace deputy_threads


    // -----------------------------------------------------------------------
    //  SUBMODULE: worker_threads — Ministros
    // -----------------------------------------------------------------------

    namespace worker_threads {

        /* art. 100 + Ley 50/1997
         * "Los demás miembros del Gobierno serán nombrados y separados por
         *  el Rey, a propuesta de su Presidente."
         * Functions (Ley 50/1997):
         *  a) Develop Government action within their Department per Cabinet agreements.
         *  b) Exercise regulatory power within their Department's remit.
         *  c) Exercise any other powers attributed by law.
         *  d) Countersign, where appropriate, the King's acts in their competence area.
         * Ministers without portfolio may exist, assigned specific governmental functions.
         * Substitution: by Real Decreto of the President; must fall on another Cabinet member. */
        static constexpr const char* APPOINTED_BY = "Rey — a propuesta del Presidente (art.100)";
        static constexpr bool MINISTERS_WITHOUT_PORTFOLIO_ALLOWED = true;

        // Exempt from in-person appearance before judges; may inform in writing.
        // If matter not known via public office: statement taken at home/official office.
        static constexpr bool EXEMPT_FROM_PERSONAL_COURT_APPEARANCE = true;

    } // namespace worker_threads


    // -----------------------------------------------------------------------
    //  SUBMODULE: kernel_council — Consejo de Ministros
    // -----------------------------------------------------------------------

    namespace kernel_council {

        /* Ley 50/1997 — collegial organ of the Government.
         * Composition: President + Vice-Presidents (if any) + Ministers.
         * State Secretaries are NOT members; may attend only to report.
         * Secretariat: Minister of the Presidency.
         * Convened by: the President.
         * Deliberations prepared by: Comisión General de Secretarios de Estado y
         *   Subsecretarios (pre-meeting filter — cannot take decisions itself).
         * Deliberations: SECRET. Minutes kept. */
        static constexpr bool DELIBERATIONS_SECRET = true;
        static constexpr const char* SECRETARY     = "Ministro de la Presidencia";

        /* Functions (Ley 50/1997):
         *  a) Approve bills (proyectos de ley) and send to Congress (or Senate).
         *  b) Approve the General State Budget bill.
         *  c) Approve Royal Decree-Laws and Legislative Royal Decrees.
         *  d) Agree negotiation and signing of international treaties + provisional application.
         *  e) Submit international treaties to the Cortes Generales (arts.94 and 96.2 CE).
         *  f) Declare states of alarm and exception; propose state of siege to Congress.
         *  g) Authorise public debt issuance or contracting of credit, when legally authorised.
         *  h) Approve implementing regulations; other regulatory provisions (after Consejo de Estado).
         *  i) Create, modify and abolish directorial organs of Ministerial Departments.
         *  j) Adopt binding programmes, plans and directives for all AGE organs.
         *  k) Any other powers conferred by CE, laws or other provisions. */
        enum class Function : uint8_t {
            APPROVE_BILLS                      = 0,  // a
            APPROVE_BUDGET_BILL                = 1,  // b
            APPROVE_DECREE_LAWS                = 2,  // c
            NEGOTIATE_SIGN_TREATIES            = 3,  // d
            SUBMIT_TREATIES_TO_CORTES          = 4,  // e
            DECLARE_ALARM_EXCEPTION_STATES     = 5,  // f — proposes siege to Congress
            ISSUE_PUBLIC_DEBT                  = 6,  // g
            APPROVE_REGULATIONS                = 7,  // h
            MANAGE_MINISTERIAL_ORGANS          = 8,  // i
            ADOPT_BINDING_DIRECTIVES           = 9,  // j
        };

    } // namespace kernel_council


    // -----------------------------------------------------------------------
    //  SUBMODULE: delegated_pools — Comisiones Delegadas del Gobierno
    // -----------------------------------------------------------------------

    namespace delegated_pools {

        /* Ley 50/1997 — collegial organs of the Government (not in the CE).
         * Created/modified/abolished: by the Cabinet (Real Decreto), at President's proposal.
         * Deliberations: SECRET. Resolutions end the administrative route (fin vía admin.).
         * Administrative general provisions: issued as "órdenes acordadas".
         *
         * Current commissions (RD 1886/2011 + RD 385/2013):
         *  1. Comisión Delegada para Asuntos Económicos
         *  2. Consejo de Seguridad Nacional (as Comisión Delegada para Seguridad Nacional)
         *  3. Comisión Delegada para Asuntos de Inteligencia (Ley 11/2002, de 6 de mayo)
         *  4. Comisión Delegada para Política Científica y Tecnológica
         *  5. Comisión Delegada para Política de Igualdad
         *  6. Comisión Delegada para Asuntos Culturales
         *
         * Each creation decree must specify:
         *  a) The Cabinet member who chairs the commission.
         *  b) The Cabinet members (and State Secretaries, if any) who compose it.
         *  c) The functions attributed to the commission.
         *  d) The member responsible for its Secretariat.
         *
         * Functions:
         *  · Examine cross-departmental matters.
         *  · Study issues requiring a joint proposal before going to Cabinet.
         *  · Resolve multi-ministry matters not requiring full Cabinet.
         *  · Any other powers delegated by Cabinet or the legal order. */
        static constexpr bool DELIBERATIONS_SECRET  = true;
        static constexpr bool ENDS_ADMIN_ROUTE      = true;
        static constexpr const char* CREATED_BY     = "Consejo de Ministros — Real Decreto";

    } // namespace delegated_pools


    // -----------------------------------------------------------------------
    //  SUBMODULE: support_services — Órganos de colaboración y apoyo
    // -----------------------------------------------------------------------

    namespace support_services {

        /* Ley 50/1997 art.7-10 — four support organs:
         *  1. Secretarios de Estado
         *  2. Comisión General de Secretarios de Estado y Subsecretarios
         *  3. Secretariado del Gobierno
         *  4. Gabinetes */

        // --- 1. SECRETARIOS DE ESTADO ---
        /* Upper organs of the AGE — NOT Cabinet members.
         * Report to their Minister (or directly to the President if attached to PM's office).
         * May hold parliamentary status (diputados/senadores).
         * Appointed/removed: by Cabinet RD, at proposal of PM or competent Minister (art.15 Ley).
         * Form the "Comisión General" together with Subsecretaries.
         * Incompatibilities: senior civil service regime. */
        static constexpr bool STATE_SECRETARY_IS_GOVT_MEMBER  = false;
        static constexpr bool STATE_SECRETARY_CAN_BE_MP       = true;
        static constexpr const char* STATE_SEC_APPOINTED_BY   =
            "Consejo de Ministros — RD — propuesta PM o Ministro competente";

        // --- 2. COMISIÓN GENERAL DE SECRETARIOS DE ESTADO Y SUBSECRETARIOS ---
        /* Composition: State Secretaries + Subsecretaries of all Ministries.
         * Chair: Vice-President; failing that, Minister of the Presidency.
         * Sole function: prepare Cabinet sessions.
         * CANNOT adopt decisions or agreements by delegation of the Government.
         * All matters going to Cabinet must pass through this body
         * (except those exempted by Cabinet's own operating rules). */
        static constexpr const char* PREP_COMMITTEE_SOLE_FUNCTION = "prepare Cabinet sessions";
        static constexpr bool PREP_COMMITTEE_CAN_DECIDE           = false;

        // --- 3. SECRETARIADO DEL GOBIERNO ---
        /* Support organ for Cabinet, Delegated Commissions and the Prep Committee.
         * Functions:
         *  a) Assist the Minister-Secretary of Cabinet.
         *  b) Send convocations to members of the collegial organs.
         *  c) Liaise with Technical Secretariats of Delegated Commissions.
         *  d) File and custody convocations, agendas and minutes.
         *  e) Ensure correct publication of Government norms in the BOE.
         * Integrated in: Ministry of the Presidency's organic structure. */

        // --- 4. GABINETES ---
        /* Political and technical support for: President, Vice-Presidents,
         *   Ministers and State Secretaries.
         * Nature: confidence and special advisory tasks — CANNOT adopt acts or resolutions
         *   belonging to AGE organs.
         * Support areas: political work, parliamentary tasks, institutional relations.
         * Member count and pay: set by Cabinet within budget appropriations.
         * Civil servants joining: move to "servicios especiales" status (or remain active).
         * Non-civil-servant staff: right to job reservation + seniority. */
        static constexpr bool GABINETE_CAN_ADOPT_ADMIN_ACTS = false;

    } // namespace support_services

} // namespace executive_process


// ============================================================================
//  MODULE: process_lifecycle
//  Spawn, terminate and caretaker modes — arts. 99-101 CE + Ley 50/1997
// ============================================================================

namespace process_lifecycle {

    // -----------------------------------------------------------------------
    //  SPAWN — PM investiture (art. 99)  ⭐ MEMORISE
    // -----------------------------------------------------------------------

    /* art. 99 — PM election procedure
     * "1. Después de cada renovación del Congreso de los Diputados, y en los
     *    demás supuestos constitucionales en que así proceda, el Rey, previa
     *    consulta con los representantes designados por los Grupos políticos
     *    con representación parlamentaria, y a través del Presidente del
     *    Congreso, propondrá un candidato a la Presidencia del Gobierno.
     *  2. El candidato propuesto expondrá ante el Congreso el programa
     *    político del Gobierno que pretenda formar y solicitará la confianza
     *    de la Cámara.
     *  3. Si el Congreso, por el voto de la mayoría absoluta de sus miembros,
     *    otorgare su confianza, el Rey le nombrará Presidente.
     *    De no alcanzarse dicha mayoría, se someterá la misma propuesta a
     *    nueva votación cuarenta y ocho horas después de la anterior, y la
     *    confianza se entenderá otorgada si obtuviere la mayoría simple.
     *  4. Si efectuadas las citadas votaciones no se otorgase la confianza,
     *    se tramitarán sucesivas propuestas en la forma prevista en los
     *    apartados anteriores.
     *  5. Si transcurrido el plazo de dos meses, a partir de la primera
     *    votación de investidura, ningún candidato hubiere obtenido la
     *    confianza del Congreso, el Rey disolverá ambas Cámaras y convocará
     *    nuevas elecciones con el refrendo del Presidente del Congreso." */

    enum class SpawnMode : uint8_t {
        ORDINARY_INVESTITURE = 0,   // post-election or after PM cese (art.99)
        CONSTRUCTIVE_CENSURE = 1,   // motion of no-confidence with alternative candidate
    };

    struct InvestitureSequence {
        // Step 1: King consults parliamentary group representatives → proposes candidate
        //         via President of Congress.
        // Step 2: Candidate presents programme before Congress + requests confidence.
        // Step 3a: Vote 1 — absolute majority → appointed PM by King.
        // Step 3b: Vote 2 (48h later, same candidate) — simple majority → appointed PM.
        // Step 4: Successive proposals if no candidate obtains confidence.
        // Step 5: After 2 months from first vote → King dissolves both chambers
        //         + calls elections, countersigned by President of Congress.

        static constexpr uint8_t  VOTE1_MAJORITY_REQUIRED = 50; // abs. majority (>50%)
        static constexpr const char* VOTE2_MAJORITY       = "mayoría simple";
        static constexpr uint8_t  VOTE2_WAIT_HOURS        = 48;
        static constexpr uint8_t  DISSOLUTION_TIMEOUT_MONTHS = 2;
        static constexpr const char* DISSOLUTION_COUNTERSIGN = "Presidente del Congreso";
    };

    // Appointment of other Cabinet members (art.100):
    /* "Los demás miembros del Gobierno serán nombrados y separados por el Rey,
     *  a propuesta de su Presidente." */
    static constexpr const char* MINISTERS_APPOINTED_BY =
        "Rey — a propuesta del Presidente (art.100)";

    // Oath (Real Decreto 707/1979):
    // PM: before the King — faithful performance of duties + loyalty to King +
    //     uphold the Constitution as fundamental norm.
    // VP/Ministers: same + secrecy of Cabinet deliberations.


    // -----------------------------------------------------------------------
    //  TERMINATE — process termination (art. 101)
    // -----------------------------------------------------------------------

    /* art. 101 — government cese
     * "1. El Gobierno cesa tras la celebración de elecciones generales, en los
     *    casos de pérdida de la confianza parlamentaria previstos en la
     *    Constitución, o por dimisión o fallecimiento de su Presidente.
     *  2. El Gobierno cesante continuará en funciones hasta la toma de posesión
     *    del nuevo Gobierno." */

    enum class CeseReason : uint8_t {
        GENERAL_ELECTIONS          = 0,  // including dissolution under art.115
        LOST_CONFIDENCE_VOTE       = 1,  // cuestión de confianza perdida (arts.112+114)
        MOTION_OF_NO_CONFIDENCE    = 2,  // moción de censura aprobada (art.113)
        PM_RESIGNATION             = 3,
        PM_DEATH                   = 4,  // VP assumes PM functions
    };

    // Individual cese:
    // VP: by King, at PM's proposal — Real Decreto.
    // Ministers: same as VP.
    // Both also cease automatically whenever the PM ceases.


    // -----------------------------------------------------------------------
    //  CARETAKER — Gobierno en funciones (art.101.2 + Ley 50/1997)
    // -----------------------------------------------------------------------

    /* "El Gobierno cesante continuará en funciones hasta la toma de posesión
     *  del nuevo Gobierno."
     *
     * Mission: facilitate formation of new Government + orderly handover.
     * Scope limited to: despacho ordinario de los asuntos públicos.
     * Exceptions for urgent / general-interest matters (must be accredited).
     *
     * Legislative delegations from the Cortes: SUSPENDED while Government
     * is in caretaker mode due to general elections. */

    // PM in caretaker mode CANNOT:
    enum class CaretakerPMBlocked : uint8_t {
        PROPOSE_DISSOLUTION_OF_CHAMBERS = 0,  // art.115
        RAISE_CONFIDENCE_VOTE           = 1,  // art.112
        PROPOSE_CONSULTATIVE_REFERENDUM = 2,  // art.92
    };

    // Government (as a whole) in caretaker mode CANNOT:
    enum class CaretakerGovtBlocked : uint8_t {
        APPROVE_BUDGET_BILL             = 0,
        SUBMIT_BILLS_TO_CORTES          = 1,
    };

    static constexpr bool LEGISLATIVE_DELEGATIONS_SUSPENDED_DURING_CARETAKER = true;

} // namespace process_lifecycle


// ============================================================================
//  MODULE: scheduler_interface
//  Kernel ↔ legislature signalling — Título V CE (arts. 108-116)
// ============================================================================

namespace scheduler_interface {

    /* art. 108 — government accountability baseline
     * "El Gobierno responde solidariamente en su gestión política ante el
     *  Congreso de los Diputados." */
    static constexpr const char* ACCOUNTABILITY_TARGET  = "Congreso de los Diputados";
    static constexpr bool SOLIDARITY_RESPONSIBILITY     = true;

    /* art. 109 — information pull
     * "Las Cámaras y sus Comisiones podrán recabar, a través de los
     *  Presidentes de aquéllas, la información y ayuda que precisen del
     *  Gobierno y de sus Departamentos y de cualesquiera autoridades del
     *  Estado y de las Comunidades Autónomas." */

    /* art. 110 — attendance and access
     * "1. Las Cámaras y sus Comisiones pueden reclamar la presencia de los
     *    miembros del Gobierno.
     *  2. Los miembros del Gobierno tienen acceso a las sesiones de las
     *    Cámaras y a sus Comisiones y la facultad de hacerse oír en ellas,
     *    y podrán solicitar que informen ante las mismas funcionarios de sus
     *    Departamentos." */

    /* art. 111 — interpellations and questions
     * "1. El Gobierno y cada uno de sus miembros están sometidos a las
     *    interpelaciones y preguntas que se le formulen en las Cámaras.
     *    Para esta clase de debate los Reglamentos establecerán un tiempo
     *    mínimo semanal.
     *  2. Toda interpelación podrá dar lugar a una moción en la que la
     *    Cámara manifieste su posición."
     *
     * Distinctions: question vs interpellation:
     *  · Questions: administrative matters — no motion possible.
     *  · Interpellations: political matters — general debate — can lead to a moción. */
    static constexpr bool QUESTION_CAN_LEAD_TO_MOTION       = false;
    static constexpr bool INTERPELLATION_CAN_LEAD_TO_MOTION = true;


    // -----------------------------------------------------------------------
    //  SIGNAL: CONFIDENCE_REQUEST — Cuestión de confianza (art. 112)  ⭐
    // -----------------------------------------------------------------------

    /* art. 112
     * "El Presidente del Gobierno, previa deliberaciónk del Consejo de
     *  Ministros, puede plantear ante el Congreso de los Diputados la
     *  cuestión de confianza sobre su programa o sobre una declaración de
     *  política general. La confianza se entenderá otorgada cuando vote a
     *  favor de la misma la mayoría simple de los Diputados." */

    struct ConfidenceVote {
        static constexpr const char* INITIATOR     = "Presidente del Gobierno";
        static constexpr const char* REQUIRES_PRIOR = "deliberación del Consejo de Ministros";
        static constexpr const char* SCOPE         = "programa o declaración de política general";
        static constexpr const char* FORUM         = "Congreso de los Diputados (NOT Senado)";
        static constexpr const char* PASS_MAJORITY = "mayoría simple";

        // Outcomes (art. 114):
        // PASS → Government continues + strengthened position.
        // FAIL → PM must resign + new investiture procedure (art.99).
        /* art. 114.1: "Si el Congreso niega su confianza al Gobierno, éste
         *  presentará su dimisión al Rey, procediéndose a continuación a la
         *  designación de Presidente del Gobierno, según lo dispuesto en el
         *  artículo 99." */
        static constexpr bool FAIL_TRIGGERS_RESIGNATION = true;
    };


    // -----------------------------------------------------------------------
    //  SIGNAL: NO_CONFIDENCE — Moción de censura (art. 113)  ⭐
    // -----------------------------------------------------------------------

    /* art. 113
     * "1. El Congreso de los Diputados puede exigir la responsabilidad política
     *    del Gobierno mediante la adopción por mayoría absoluta de la moción de
     *    censura.
     *  2. La moción de censura deberá ser propuesta al menos por la décima
     *    parte de los Diputados, y habrá de incluir un candidato a la
     *    Presidencia del Gobierno.
     *  3. La moción de censura no podrá ser votada hasta que transcurran cinco
     *    días desde su presentación. En los dos primeros días de dicho plazo
     *    podrán presentarse mociones alternativas.
     *  4. Si la moción de censura no fuere aprobada por el Congreso, sus
     *    signatarios no podrán presentar otra durante el mismo período de
     *    sesiones." */

    struct MotionOfNoCConfidence {
        static constexpr const char* INITIATOR      = "Congreso de los Diputados";
        static constexpr float MIN_SIGNATORIES_FRACTION = 0.10f;  // 1/10 of deputies
        static constexpr bool MUST_INCLUDE_CANDIDATE = true;      // constructive motionS
        static constexpr uint8_t COOLING_PERIOD_DAYS = 5;
        static constexpr uint8_t ALTERNATIVE_MOTIONS_WINDOW_DAYS = 2; // first 2 of 5
        static constexpr const char* PASS_MAJORITY  = "mayoría absoluta del Congreso";

        // Outcomes (art. 114.2):
        // PASS → Government resigns; included candidate automatically invested as PM;
        //        King appoints candidate as PM.
        /* art. 114.2: "Si el Congreso adopta una moción de censura, el Gobierno
         *  presentará su dimisión al Rey y el candidato incluido en aquélla se
         *  entenderá investido de la confianza de la Cámara a los efectos
         *  previstos en el artículo 99. El Rey le nombrará Presidente del Gobierno." */
        static constexpr bool PASS_AUTO_INVESTS_CANDIDATE   = true;
        static constexpr bool FAIL_BLOCKS_NEW_MOTION_IN_SAME_PERIOD = true;
    };


    // -----------------------------------------------------------------------
    //  SIGNAL: DISSOLUTION — art. 115
    // -----------------------------------------------------------------------

    /* art. 115
     * "1. El Presidente del Gobierno, previa deliberación del Consejo de
     *    Ministros, y bajo su exclusiva responsabilidad, podrá proponer la
     *    disolución del Congreso, del Senado o de las Cortes Generales, que
     *    será decretada por el Rey. El decreto de disolución fijará la fecha
     *    de las elecciones.
     *  2. La propuesta de disolución no podrá presentarse cuando esté en
     *    trámite una moción de censura.
     *  3. No procederá nueva disolución antes de que transcurra un año desde
     *    la anterior, salvo lo dispuesto en el artículo 99, apartado 5." */

    struct Dissolution {
        static constexpr const char* PROPOSER      = "Presidente del Gobierno";
        static constexpr const char* REQUIRES_PRIOR = "deliberación del Consejo de Ministros";
        static constexpr const char* RESPONSIBILITY = "exclusiva del Presidente";
        static constexpr const char* DECREED_BY    = "El Rey";
        // Dissolution decree must fix the election date.
        static constexpr bool BLOCKED_DURING_NO_CONFIDENCE_MOTION = true;
        static constexpr uint8_t MIN_MONTHS_BETWEEN_DISSOLUTIONS  = 12;
        // Exception to 12-month rule: art.99.5 (no PM after 2-month investiture deadlock)
    };

} // namespace scheduler_interface


#endif // PROCESS_MANAGER_HPP
