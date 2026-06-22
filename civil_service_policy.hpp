/**
 * @file civil_service_policy.hpp
 * @brief Policy configuration layer for public-sector workforce management,
 *        transparency subsystem and sustainable-development target registry.
 *
 * @ref Covered specs:
 *   - Agenda 2030 / ODS (Cumbre ONU, 25-sep-2015; 193 países)
 *   - V Plan de Gobierno Abierto 2025-2029 (aprobado 06-oct-2025)
 *   - Ley 19/2013, de 9 de diciembre (arts. 1-32 + RD 615/2024 Consejo CTBG)
 *   - TREBEP – Real Decreto Legislativo 5/2015, de 30 de octubre (arts. 1-100)
 *   - RD 364/1995, de 10 de marzo (arts. 36-76; provisión, concurso, libre designación)
 */

#ifndef CIVIL_SERVICE_POLICY_HPP
#define CIVIL_SERVICE_POLICY_HPP

#include <cstdint>
#include <array>

// ============================================================
// NAMESPACE: open_gov
//   Gobierno Abierto, Agenda 2030, ODS, V Plan
// ============================================================
namespace open_gov {

/* OCDE Recomendación del Consejo sobre Gobierno Abierto, 14/12/2017 —
 * "Gobierno Abierto es una cultura de gobernanza que promueve los principios
 *  de transparencia, integridad, rendición de cuentas y participación de las
 *  partes interesadas en apoyo de la democracia y el crecimiento inclusivo." */
struct GovernanceCulture {
    static constexpr const char* TRANSPARENCY   = "transparencia";
    static constexpr const char* INTEGRITY      = "integridad";
    static constexpr const char* ACCOUNTABILITY = "rendición de cuentas";
    static constexpr const char* PARTICIPATION  = "participación de partes interesadas";
};

/* OGP – Alianza para el Gobierno Abierto (Open Government Partnership)
 * Fundada en septiembre de 2011; organización multilateral.
 * España se unió en el mismo año de su fundación.
 * La evaluación de compromisos la realiza el MRI (Mecanismo de Revisión Independiente). */
struct OGP {
    static constexpr uint16_t FOUNDED_YEAR       = 2011;
    static constexpr const char* EVALUATOR       = "MRI – Mecanismo de Revisión Independiente";
    static constexpr bool SPAIN_FOUNDING_MEMBER  = true;  // ⭐
};

/* Planes de Acción nacionales de Gobierno Abierto – ámbito nacional:
 *   I  Plan (2012-2014): aprobación de la Ley de Transparencia
 *   II Plan (2014-2016): puesta en marcha del Portal de la Transparencia
 *   III Plan (2017-2019): creación del Foro de Gobierno Abierto
 *   IV Plan (2020-2024): ratificación Convenio Tromsø; Sistema de Integridad AGE */
enum class ActionPlan : uint8_t {
    I_TRANSPARENCY_LAW    = 1,  // 2012-2014
    II_PORTAL_LAUNCH      = 2,  // 2014-2016
    III_OPEN_GOV_FORUM    = 3,  // 2017-2019
    IV_TROMSO_INTEGRITY   = 4,  // 2020-2024
};

/* V Plan de Gobierno Abierto 2025-2029
 * Aprobado el 6 de octubre de 2025.
 * Estructura: 10 compromisos, 218 iniciativas.
 * Incluye: AGE, Estado Abierto (CCAA, Ciudad Autónoma de Melilla, FEMP). */
struct VActionPlan {
    static constexpr uint16_t APPROVED_YEAR      = 2025;
    static constexpr uint8_t  APPROVED_MONTH     = 10;   // octubre
    static constexpr uint8_t  APPROVED_DAY       = 6;    // ⭐
    static constexpr uint16_t PERIOD_START       = 2025;
    static constexpr uint16_t PERIOD_END         = 2029;
    static constexpr uint8_t  COMMITMENTS        = 10;   // ⭐
    static constexpr uint16_t INITIATIVES        = 218;
};

/* Los 10 compromisos del V Plan — ⭐ memorizar lista */
enum class VPlanCommitment : uint8_t {
    C01_PARTICIPATION_CIVIC_SPACE        = 1,
    C02_TRANSPARENCY_INFO_ACCESS         = 2,
    C03_INTEGRITY_ACCOUNTABILITY         = 3,
    C04_OPEN_ADMINISTRATION              = 4,
    C05_DIGITAL_GOVERNANCE_AI            = 5,
    C06_CLEAR_OPEN_ACCOUNTS              = 6,
    C07_TRUTHFUL_INFO_ECOSYSTEM          = 7,
    C08_DIFFUSION_TRAINING_PROMOTION     = 8,
    C09_OPEN_GOV_OBSERVATORY             = 9,
    C10_OPEN_STATE                       = 10,
};

/* Órganos de gobernanza del Gobierno Abierto en España (AGE):
 *   - Dirección General de Gobernanza Pública (Min. Política Territorial y FFPP):
 *     impulso, coordinación y seguimiento de los planes.
 *   - Grupo interministerial de Gobierno Abierto: coordinado por la DGGP.
 *   - Comisión Sectorial de Gobierno Abierto: coordinación entre AAPP.
 *   - Foro de Gobierno Abierto: AAPP + sociedad civil (partes iguales). */
struct SpainOpenGovBodies {
    static constexpr const char* COORD_UNIT   = "DGGP – Dirección General de Gobernanza Pública";
    static constexpr const char* MINISTRY     = "Ministerio de Política Territorial y Función Pública";
    static constexpr const char* INTER_GROUP  = "Grupo interministerial de Gobierno Abierto";
    static constexpr const char* SECTOR_COMM  = "Comisión Sectorial de Gobierno Abierto";
    static constexpr const char* CIVIC_FORUM  = "Foro de Gobierno Abierto";
    static constexpr bool FORUM_EQUAL_PARTS   = true;  // AAPP = sociedad civil
};

// ---- Agenda 2030 ----

/* La Agenda 2030 para el Desarrollo Sostenible — compromiso global de 193 países,
 * adoptado el 25 de septiembre de 2015, para un plan de acción "a favor de las
 * personas, el planeta y la prosperidad". Pretende fortalecer la paz universal
 * y el acceso a la justicia. */
struct Agenda2030 {
    static constexpr uint16_t ADOPTED_YEAR    = 2015;
    static constexpr uint8_t  ADOPTED_MONTH   = 9;
    static constexpr uint8_t  ADOPTED_DAY     = 25;    // ⭐
    static constexpr uint16_t SIGNATORY_COUNT = 193;   // ⭐
    static constexpr uint8_t  SDG_COUNT       = 17;    // ⭐
    static constexpr uint8_t  TARGET_COUNT    = 169;
    static constexpr uint16_t INDICATOR_COUNT = 232;   // indicadores mundiales
    static constexpr const char* SLOGAN       = "personas, planeta y prosperidad";
    static constexpr const char* MONITOR_ES   = "Instituto Nacional de Estadística (INE)";
};

/* Los 17 Objetivos de Desarrollo Sostenible (ODS) — ⭐ VIP: memorizar los 17 */
enum class SDG : uint8_t {
    ODS01_NO_POVERTY              = 1,   // Erradicar la pobreza
    ODS02_ZERO_HUNGER             = 2,   // Poner fin al hambre
    ODS03_GOOD_HEALTH             = 3,   // Garantizar vida sana y promover el bienestar
    ODS04_QUALITY_EDUCATION       = 4,   // Educación inclusiva, equitativa y de calidad
    ODS05_GENDER_EQUALITY         = 5,   // Lograr igualdad entre géneros
    ODS06_CLEAN_WATER             = 6,   // Garantizar agua limpia y saneada
    ODS07_CLEAN_ENERGY            = 7,   // Energía asequible y no contaminante
    ODS08_DECENT_WORK             = 8,   // Trabajo decente y crecimiento económico sostenido
    ODS09_INDUSTRY_INNOVATION     = 9,   // Infraestructuras sostenibles e innovación
    ODS10_REDUCED_INEQUALITIES    = 10,  // Reducir las desigualdades
    ODS11_SUSTAINABLE_CITIES      = 11,  // Ciudades sostenibles
    ODS12_RESPONSIBLE_CONSUMPTION = 12,  // Consumo responsable
    ODS13_CLIMATE_ACTION          = 13,  // Combatir el cambio climático
    ODS14_LIFE_BELOW_WATER        = 14,  // Conservar la vida submarina
    ODS15_LIFE_ON_LAND            = 15,  // Proteger ecosistemas terrestres
    ODS16_PEACE_JUSTICE           = 16,  // Impulsar sociedades pacíficas ⭐ (acelerador GO)
    ODS17_PARTNERSHIPS            = 17,  // Fortalecer alianzas para el DS
};

/* Estrategia de Desarrollo Sostenible 2030 — aprobada por Consejo de Ministros
 * el 5 de junio de 2021. Basada en el Plan de Acción para la Agenda 2030
 * aprobado en 2018.
 * Estructura: 8 retos país + 8 políticas aceleradoras.
 * Ministerio competente: Ministerio de Derechos Sociales, Consumo y Agenda 2030. */
enum class PaisReto : uint8_t {
    R1_END_POVERTY_INEQUALITY      = 1,
    R2_CLIMATE_ENVIRONMENTAL       = 2,
    R3_GENDER_GAP_DISCRIMINATION   = 3,
    R4_ECONOMIC_CONCENTRATION      = 4,
    R5_PRECARIOUS_LABOUR           = 5,
    R6_PUBLIC_SERVICES_CRISIS      = 6,
    R7_GLOBAL_INJUSTICE_RIGHTS     = 7,
    R8_RURAL_DEMOGRAPHIC           = 8,
};

/* Gobernanza de la Estrategia 2030 — tres niveles:
 *   1. Comisión Delegada del Gobierno para la Agenda 2030 (15 ministerios)
 *   2. Conferencia Sectorial para la Agenda 2030 (AAPP + FEMP)
 *   3. Consejo de Desarrollo Sostenible (academia, empresas, sindicatos, ecologistas)
 * + Comisión Mixta de coordinación y seguimiento (acompañamiento parlamentario). */
struct Agenda2030Governance {
    static constexpr uint8_t DELEGATED_COMM_MINISTRIES = 15;  // ⭐
};

} // namespace open_gov


// ============================================================
// NAMESPACE: transparency_bus
//   Ley 19/2013, de 9 de diciembre
// ============================================================
namespace transparency_bus {

/* art. 1 — Objeto de la Ley 19/2013
 * Ampliar y reforzar la transparencia de la actividad pública, regular y
 * garantizar el derecho de acceso a la información relativa a aquella actividad
 * y establecer las obligaciones de buen gobierno que deben cumplir los
 * responsables públicos así como las consecuencias de su incumplimiento.
 * Estructura: Título Preliminar + 3 Títulos = 40 artículos. */
struct LeyTransparencia {
    static constexpr uint16_t LAW_YEAR      = 2013;
    static constexpr uint8_t  LAW_MONTH     = 12;
    static constexpr uint8_t  LAW_DAY       = 9;
    static constexpr uint8_t  TOTAL_ARTS    = 40;
    static constexpr uint8_t  TITLE_COUNT   = 4;  // Preliminar + I + II + III
};

// ---- Título I — Ámbito de aplicación ----

/* art. 2 — Ámbito subjetivo de aplicación (Título I) — ⭐ VIP
 * Se aplica a:
 *  a) AGE, CCAA, Ciudades de Ceuta y Melilla, Entidades Locales.
 *  b) Entidades gestoras y servicios comunes Seg. Social + mutuas colaboradoras.
 *  c) Organismos autónomos, Agencias Estatales, EPEs y entidades de DP con
 *     independencia funcional / autonomía especial que ejerzan regulación o
 *     supervisión externa.
 *  d) Entidades de DP con personalidad jurídica propia vinculadas a AAPP,
 *     incluidas las Universidades públicas.
 *  e) Corporaciones de DP en sus actividades sujetas a Derecho Administrativo.
 *  f) Casa de S.M. el Rey, Congreso, Senado, TC, CGPJ, Banco de España,
 *     Consejo de Estado, Defensor del Pueblo, Tribunal de Cuentas, CES
 *     y análogos autonómicos, en sus actividades sujetas a DA.
 *  g) Sociedades mercantiles con participación pública directa/indirecta > 50 %.
 *  h) Fundaciones del sector público.
 *  i) Asociaciones constituidas por AAPP u organismos de los anteriores.
 * A efectos de este Título, "AAPP" = entidades a)-d). */
enum class ScopeEntity : uint8_t {
    A_AGE_CCAA_EELL              = 0,
    B_SOCIAL_SECURITY            = 1,
    C_OO_AUTONOMOS_AGENCIAS      = 2,
    D_ENTITIES_JURIDICAL_PERSON  = 3,  // incluye universidades públicas
    E_CORPO_DERECHO_PUBLICO      = 4,
    F_CONSTITUTIONAL_BODIES      = 5,  // ⭐ Casa Rey, Congreso, Senado, TC, CGPJ…
    G_MERCANTILE_GT_50PCT        = 6,
    H_PUBLIC_SECTOR_FOUNDATIONS  = 7,
    I_ASSOCIATIONS_AAPP          = 8,
};

/* art. 3 — Otros sujetos obligados (solo Capítulo II – publicidad activa)
 *  a) Partidos políticos, organizaciones sindicales y organizaciones empresariales.
 *  b) Entidades privadas con ayudas/subvenciones públicas > 100.000 € en un año,
 *     O que al menos el 40 % de sus ingresos anuales sean ayuda/subvención pública
 *     y dicha cuantía alcance mínimo 5.000 €. */
struct OtherObligedSubjects {
    static constexpr uint32_t SUBSIDY_THRESHOLD_EUR     = 100000;  // ⭐
    static constexpr float    INCOME_RATIO_THRESHOLD    = 0.40f;   // ⭐ 40 %
    static constexpr uint16_t MINIMUM_SUBSIDY_EUR       = 5000;
};

// ---- Título I, Capítulo II — Publicidad activa ----

/* art. 5 — Principios generales de publicidad activa
 * Los sujetos del art. 2.1 publicarán de forma periódica y actualizada la
 * información relevante para la transparencia de su actividad.
 * La información será comprensible, de acceso fácil y gratuito y accesible
 * a personas con discapacidad (principio de accesibilidad universal).
 * Entidades sin ánimo de lucro con presupuesto < 50.000 € podrán usar medios
 * electrónicos puestos a disposición por la AAPP de que dependan. */
struct ActivePublicityPrinciples {
    static constexpr bool PERIODIC_UPDATE_REQUIRED     = true;
    static constexpr bool FREE_ACCESS                  = true;
    static constexpr bool UNIVERSAL_ACCESSIBILITY      = true;
    static constexpr uint32_t NONPROFIT_BUDGET_LIMIT   = 50000;  // exención formato
};

/* art. 9 — Control de las obligaciones de publicidad activa — ⭐ VIP
 * Controlador: Consejo de Transparencia y Buen Gobierno (CTBG).
 * El incumplimiento reiterado de las obligaciones de publicidad activa
 * tendrá la consideración de INFRACCIÓN GRAVE a efectos disciplinarios. */
struct ActivePublicityControl {
    static constexpr const char* CONTROLLER           = "Consejo de Transparencia y Buen Gobierno";
    static constexpr const char* BREACH_SEVERITY      = "infracción grave";  // ⭐
    static constexpr bool CTBG_CAN_ISSUE_RESOLUTIONS  = true;
};

/* art. 10 — Portal de la Transparencia — ⭐ VIP
 * Desarrollado por la AGE, dependiente del Ministerio de la Presidencia.
 * Incluye la información de la AGE cuyo acceso sea más frecuente.
 * CCAA, Ceuta, Melilla y EELL podrán adoptar medidas complementarias. */
struct TransparencyPortal {
    static constexpr const char* OWNER_MINISTRY = "Ministerio de la Presidencia";
    static constexpr bool AGE_RESPONSIBLE       = true;  // ⭐
};

/* art. 11 — Principios técnicos del Portal de la Transparencia — ⭐ VIP
 *  a) Accesibilidad: información estructurada para facilitar búsqueda.
 *  b) Interoperabilidad: conforme al ENI (RD 4/2010, de 8 enero).
 *  c) Reutilización: formatos conformes a Ley 37/2007 sobre reutilización
 *     de información del sector público. */
enum class PortalTechPrinciple : uint8_t {
    ACCESSIBILITY      = 0,  // a) — identificación y búsqueda
    INTEROPERABILITY   = 1,  // b) — ENI RD 4/2010
    REUSE              = 2,  // c) — Ley 37/2007
};

// ---- Título I, Capítulo III — Derecho de acceso ----

/* art. 12 — Derecho de acceso a la información pública
 * Todas las personas tienen derecho a acceder a la información pública,
 * conforme al art. 105.b) de la Constitución Española. */

/* art. 13 — Información pública
 * Contenidos o documentos, en cualquier formato o soporte, que obren en
 * poder de los sujetos del ámbito de aplicación y hayan sido elaborados o
 * adquiridos en el ejercicio de sus funciones. */

/* art. 14 — Límites al derecho de acceso — ⭐ VIP
 * El acceso podrá limitarse cuando su ejercicio suponga un perjuicio para: */
enum class AccessLimit : uint8_t {
    A_NATIONAL_SECURITY         = 0,
    B_DEFENCE                   = 1,
    C_FOREIGN_RELATIONS         = 2,
    D_PUBLIC_SAFETY             = 3,
    E_CRIMINAL_ADMIN_DISCIPLINE = 4,
    F_JUDICIAL_EQUALITY         = 5,
    G_ADMIN_SUPERVISION         = 6,
    H_ECONOMIC_COMMERCIAL       = 7,
    I_ECONOMIC_MONETARY_POLICY  = 8,
    J_PROFESSIONAL_SECRET_IP    = 9,
    K_DECISION_CONFIDENTIALITY  = 10,
    L_ENVIRONMENT_PROTECTION    = 11,
};

/* art. 17 — Solicitud de acceso a la información — ⭐ VIP
 * Se inicia con solicitud al titular del órgano/entidad que posea la info.
 * Campos requeridos:
 *   a) Identidad del solicitante.
 *   b) Información solicitada.
 *   c) Dirección de contacto (preferentemente electrónica).
 *   d) Modalidad de acceso preferida (opcional).
 * El solicitante NO está obligado a motivar la solicitud.
 * Se puede usar cualquier lengua cooficial del Estado en el territorio. */
struct AccessRequest {
    static constexpr bool MOTIVATION_REQUIRED  = false;  // ⭐
    static constexpr bool COOFFICIAL_LANG_OK   = true;
};

/* art. 18 — Causas de inadmisión — ⭐ VIP
 * Se inadmitirán a trámite, mediante resolución motivada, las solicitudes: */
enum class InadmissionCause : uint8_t {
    A_INFO_IN_ELABORATION       = 0,  // en curso de elaboración o publicación general
    B_AUXILIARY_INTERNAL_INFO   = 1,  // notas, borradores, opiniones, informes internos
    C_REQUIRES_REELABORATION    = 2,  // divulgación exige acción previa de reelaboración
    D_WRONG_BODY_UNKNOWN_COMP   = 3,  // órgano no posee la info y se desconoce competente
    E_REPETITIVE_ABUSIVE        = 4,  // manifiestamente repetitivas o carácter abusivo
};

/* art. 19 — Tramitación
 * Plazo para concretar info insuficiente: 10 días (si no, desistimiento).
 * Plazo de alegaciones de terceros afectados: 15 días.
 * Si la info fue elaborada principalmente por otro órgano: se remite a éste. */
struct AccessRequestProcessing {
    static constexpr uint8_t CLARIFICATION_DAYS  = 10;  // ⭐
    static constexpr uint8_t THIRD_PARTY_DAYS    = 15;  // ⭐
};

/* art. 20 — Resolución
 * Plazo máximo de resolución: 1 mes desde recepción.
 * Ampliable 1 mes más por volumen/complejidad, previa notificación.
 * Silencio = desestimación.
 * Incumplimiento reiterado de plazos = INFRACCIÓN GRAVE.
 * Recurso directo ante Jurisdicción Contencioso-administrativa
 * (sin perjuicio de reclamación potestativa art. 24). */
struct AccessResolution {
    static constexpr uint8_t  RESOLUTION_MONTHS      = 1;  // ⭐
    static constexpr uint8_t  EXTENSION_MONTHS       = 1;
    static constexpr bool     SILENCE_IS_DENIAL       = true;  // ⭐
    static constexpr const char* DELAY_BREACH_LEVEL  = "infracción grave";
};

/* art. 21 — Unidades de información — ⭐ VIP
 * En el ámbito de la AGE, existirán unidades especializadas con funciones: */
enum class InfoUnitFunction : uint8_t {
    A_GATHER_DISSEMINATE        = 0,  // recabar y difundir info cap. II
    B_RECEIVE_PROCESS_REQUESTS  = 1,  // recibir y tramitar solicitudes
    C_INTERNAL_PROCEDURES       = 2,  // trámites internos para dar acceso
    D_MONITOR_CONTROL           = 3,  // seguimiento y control de tramitación
    E_MAINTAIN_REGISTRY         = 4,  // llevar registro de solicitudes
    F_ENSURE_WEB_AVAILABILITY   = 5,  // disponibilidad web/sede electrónica
    G_UPDATE_CONTENT_MAP        = 6,  // mantener mapa de contenidos actualizado
    H_GENERAL_COMPLIANCE        = 7,  // todas las necesarias para correcta aplicación
};

/* art. 22 — Formalización del acceso
 * Preferentemente por vía electrónica.
 * Si no puede darse en el momento de la notificación: plazo máximo 10 días.
 * Si hay oposición de tercero: esperar firmeza de resolución contencioso.
 * Acceso gratuito; las copias/trasposición de formato pueden generar exacciones. */
struct AccessFormalization {
    static constexpr bool     PREFERRED_ELECTRONIC   = true;
    static constexpr uint8_t  MAX_DAYS_AFTER_NOTIFY  = 10;  // ⭐
    static constexpr bool     FREE_OF_CHARGE         = true;
};

/* art. 24 — Reclamación ante el CTBG — ⭐ VIP
 * Carácter potestativo y previo a la vía contencioso-administrativa.
 * Plazo interposición: 1 mes desde notificación o efecto silencio.
 * Plazo máximo resolución CTBG: 3 meses → silencio = desestimación.
 * CTBG comunica resoluciones al Defensor del Pueblo.
 * Las CCAA pueden atribuir competencia a órgano específico propio. */
struct CTBGClaim {
    static constexpr uint8_t  FILING_MONTHS          = 1;   // ⭐
    static constexpr uint8_t  RESOLUTION_MONTHS      = 3;   // ⭐
    static constexpr bool     SILENCE_IS_DENIAL       = true;
    static constexpr bool     OPTIONAL_PRIOR_ADMIN   = true;  // potestativo ⭐
    static constexpr const char* NOTIFIED_BODY       = "Defensor del Pueblo";
};

// ---- Título II — Buen Gobierno ----

/* art. 25 — Ámbito de aplicación del Buen Gobierno — ⭐ VIP
 * En AGE: miembros del Gobierno, Secretarios de Estado y demás altos cargos
 * de la AGE y del sector público estatal (DP o privado), vinculados/dependientes.
 * Se considera "alto cargo" según normativa de conflictos de intereses.
 * En CCAA/EELL: altos cargos o asimilados conforme a su normativa,
 * incluidos miembros de Juntas de Gobierno de Entidades Locales.
 * No afecta a la condición de cargo electo. */
struct GoodGovScope {
    static constexpr bool APPLIES_GOVERNMENT_MEMBERS   = true;  // ⭐
    static constexpr bool APPLIES_STATE_SECRETARIES    = true;
    static constexpr bool APPLIES_HIGH_OFFICERS        = true;
    static constexpr bool APPLIES_LOCAL_GOV_BOARDS     = true;  // Juntas de Gobierno EE.LL.
    static constexpr bool ELECTIVE_STATUS_PRESERVED    = true;
};

/* art. 32 — Prescripción de infracciones y sanciones (Título II — Buen Gobierno) — ⭐ VIP
 * NOTA: distintos plazos que los del TREBEP (art. 97).
 * Infracciones: muy graves → 5 años; graves → 3 años; leves → 1 año.
 * Sanciones:    muy graves → 5 años; graves → 3 años; leves → 1 año. */
struct GoodGovPrescription {
    static constexpr uint8_t BREACH_VERY_SERIOUS_YEARS = 5;  // ⭐
    static constexpr uint8_t BREACH_SERIOUS_YEARS      = 3;
    static constexpr uint8_t BREACH_MINOR_YEARS        = 1;
    static constexpr uint8_t SANCTION_VERY_SERIOUS_YEARS = 5;
    static constexpr uint8_t SANCTION_SERIOUS_YEARS    = 3;
    static constexpr uint8_t SANCTION_MINOR_YEARS      = 1;
};

// ---- Título III — Consejo de Transparencia y Buen Gobierno ----
// Referencia actualizada: RD 615/2024, de 2 de julio (Estatuto del CTBG, AAI)

/* RD 615/2024, art. 1 — Naturaleza
 * El Consejo de Transparencia y Buen Gobierno es una Autoridad Administrativa
 * Independiente (AAI) de ámbito estatal, regulada en arts. 109-110 Ley 40/2015.
 * Denominación oficial: «Consejo de Transparencia y Buen Gobierno, A.A.I.»
 * Vinculado a la AGE a través del Ministerio para la Transformación Digital
 * y de la Función Pública. Actúa con plena autonomía e independencia. */
struct CTBG {
    static constexpr const char* OFFICIAL_NAME = "Consejo de Transparencia y Buen Gobierno, A.A.I.";
    static constexpr const char* PARENT_MIN    = "Ministerio para la Transformación Digital y de la FP";
    static constexpr bool        INDEPENDENT   = true;  // ⭐
    static constexpr const char* LEGAL_REF     = "arts. 109-110 Ley 40/2015 + RD 615/2024";
};

/* RD 615/2024, art. 3 — Funciones del CTBG */
enum class CTBGFunction : uint8_t {
    A_ADOPT_RECOMMENDATIONS      = 0,  // para mejor cumplimiento Ley 19/2013
    B_ADVISE_TRANSPARENCY        = 1,  // asesorar en transparencia y acceso
    C_MANDATORY_REPORT_NORMS     = 2,  // informar preceptivamente proyectos normativos
    D_EVALUATE_LAW_APPLICATION   = 3,  // evaluar grado de aplicación de la Ley
    E_PROMOTE_BEST_PRACTICES     = 4,  // elaborar recomendaciones/directrices
    F_TRAINING_AWARENESS         = 5,  // formación y sensibilización
    G_COLLABORATE_PEER_BODIES    = 6,  // colaborar con órganos análogos
    H_OTHER_LEGAL_ASSIGNED       = 7,  // atribuidas por norma legal/reglamentaria
};

/* RD 615/2024, art. 9 — Memoria anual
 * Contenido: funcionamiento orgánico, actividades, evaluación Ley 19/2013.
 * Se remite a las Cortes Generales; la Presidencia comparece ante la
 * Comisión parlamentaria correspondiente. */
struct CTBGAnnualReport {
    static constexpr const char* RECIPIENT = "Cortes Generales";
    static constexpr bool PRESIDENT_APPEARANCE = true;  // comparecencia parlamentaria
};

/* RD 615/2024, art. 11 — Estructura orgánica del CTBG — ⭐ VIP
 * 1. Presidencia del CTBG.
 * 2. Comisión de Transparencia y Buen Gobierno.
 * De la Presidencia dependen directamente (nivel subdirección general):
 *   a) Subdirección General de Transparencia y Buen Gobierno.
 *   b) Subdirección General de Reclamaciones de ámbito estatal.
 *   c) Subdirección General de Reclamaciones de CCAA y EELL.
 *   d) Secretaría General.
 *   e) Gabinete (apoyo y asistencia inmediata). */
enum class CTBGOrgUnit : uint8_t {
    PRESIDENCY                   = 0,
    COMMISSION_TRANSPARENCY_BG   = 1,
    SUBDIR_TRANSPARENCY_BG       = 2,  // a) nivel subdirección general
    SUBDIR_CLAIMS_STATE          = 3,  // b)
    SUBDIR_CLAIMS_CCAA_EELL      = 4,  // c)
    SECRETARY_GENERAL            = 5,  // d)
    CABINET                      = 6,  // e) apoyo y asistencia inmediata
};

/* RD 615/2024, art. 17 — Propuesta y nombramiento de vocales — ⭐ VIP
 * Los vocales de la Comisión de Transparencia y Buen Gobierno son propuestos por:
 *  a) Congreso de los Diputados → un Diputado/a.
 *  b) Senado → un Senador/a.
 *  c) Tribunal de Cuentas → un Consejero/a.
 *  d) Defensor del Pueblo → un representante.
 *  e) AEPD → un representante.
 *  f) Ministerio para la Transformación Digital y FP → rep. de la Secretaría de Estado de FP.
 *  g) AIReF → un representante.
 * Los de d)-g) deben tener mínimo rango de Subdirección General.
 * Nombrados y cesados por acuerdo del Gobierno; principio de presencia equilibrada. */
enum class CTBGVocalProposer : uint8_t {
    A_CONGRESO            = 0,  // Diputado/a
    B_SENADO              = 1,  // Senador/a
    C_TRIBUNAL_CUENTAS    = 2,  // Consejero/a
    D_DEFENSOR_PUEBLO     = 3,  // representante
    E_AEPD                = 4,  // Agencia Española Protección de Datos
    F_MIN_DIGITAL_FP      = 5,  // rep. Secretaría Estado Función Pública
    G_AIREF               = 6,  // Autoridad Independiente de Responsabilidad Fiscal
};

struct CTBGVocalRequirements {
    static constexpr const char* MIN_RANK_D_TO_G   = "Subdirección General";  // ⭐
    static constexpr bool        GENDER_BALANCE     = true;  // presencia equilibrada
    static constexpr const char* APPOINTING_BODY    = "Gobierno";
};

} // namespace transparency_bus


// ============================================================
// NAMESPACE: workforce_mgr
//   TREBEP — RDL 5/2015 y RD 364/1995
// ============================================================
namespace workforce_mgr {

/* TREBEP — RDL 5/2015, de 30 de octubre
 * Estructura: 8 Títulos, 100 artículos, 17 Disp. Adicionales,
 * 9 Disp. Transitorias, 1 Disp. Derogatoria, 4 Disp. Finales. */
struct TREBEPMetadata {
    static constexpr uint8_t  TITLE_COUNT     = 8;
    static constexpr uint8_t  ARTICLE_COUNT   = 100;
    static constexpr uint8_t  ADDL_PROVISIONS = 17;
    static constexpr uint8_t  TRANS_PROVS     = 9;
    static constexpr uint8_t  FINAL_PROVS     = 4;
    static constexpr uint16_t RDL_YEAR        = 2015;
    static constexpr uint8_t  RDL_NUM         = 5;
};

// ---- Título I — Objeto y ámbito de aplicación ----

/* art. 1.3 — Fundamentos de actuación del Estatuto — ⭐ VIP */
enum class TREBEPPrinciple : uint8_t {
    A_SERVICE_CITIZENS           = 0,  // servicio a ciudadanos e intereses generales
    B_EQUALITY_MERIT_CAPACITY    = 1,  // igualdad, mérito y capacidad en acceso y promoción
    C_RULE_OF_LAW                = 2,  // sometimiento pleno a la ley y al Derecho
    D_GENDER_EQUALITY            = 3,  // igualdad de trato entre mujeres y hombres
    E_OBJECTIVITY_IMPARTIALITY   = 4,  // objetividad, profesionalidad, inamovilidad FC
    F_EFFICIENT_HR_PLANNING      = 5,  // eficacia en planificación y gestión RRHH
    G_CONTINUOUS_DEVELOPMENT     = 6,  // desarrollo y cualificación profesional permanente
    H_TRANSPARENCY               = 7,  // transparencia
    I_EVALUATION_ACCOUNTABILITY  = 8,  // evaluación y responsabilidad en la gestión
    J_HIERARCHY                  = 9,  // jerarquía en atribución y desempeño
    K_COLLECTIVE_NEGOTIATION     = 10, // negociación colectiva y participación
    L_INTER_ADMIN_COOPERATION    = 11, // cooperación entre AAPP
};

/* art. 2 — Ámbito de aplicación del TREBEP — ⭐ VIP
 * Se aplica al personal funcionario y (en lo que proceda) personal laboral de: */
enum class TREBEPScopeAdmin : uint8_t {
    A_AGE                        = 0,
    B_CCAA_CEUTA_MELILLA         = 1,
    C_ENTIDADES_LOCALES          = 2,
    D_PUBLIC_BODIES_AGENCIES     = 3,  // organismos públicos, agencias, entidades DP
    E_UNIVERSIDADES_PUBLICAS     = 4,
};

// ---- Título II — Clases de personal ----

/* art. 8 — Concepto y clases de empleados públicos — ⭐ VIP
 * Son empleados públicos quienes desempeñan funciones retribuidas en las
 * Administraciones Públicas al servicio de los intereses generales. */
enum class PublicEmployeeClass : uint8_t {
    CAREER_OFFICIAL              = 0,  // a) Funcionarios de carrera
    INTERIM_OFFICIAL             = 1,  // b) Funcionarios interinos
    LABOUR_STAFF                 = 2,  // c) Personal laboral (fijo/indefinido/temporal)
    EVENTUAL_STAFF               = 3,  // d) Personal eventual
};

/* art. 9 — Funcionarios de carrera
 * Vinculados por nombramiento legal; relación estatutaria de DA; servicios
 * retribuidos de carácter permanente.
 * EXCLUSIVIDAD: ejercicio de funciones que impliquen participación directa/indirecta
 * en potestades públicas o salvaguarda de intereses generales del Estado → solo FC. */
struct CareerOfficial {
    static constexpr bool PERMANENT          = true;
    static constexpr bool EXCLUSIVE_POWERS   = true;  // potestades públicas solo FC ⭐
};

/* art. 10 — Funcionarios interinos
 * Nombrados por NECESIDAD Y URGENCIA expresamente justificadas, con carácter temporal.
 * Causas habilitantes:
 *  a) Plazas vacantes sin posible cobertura por FC → máx. 3 años.
 *  b) Sustitución transitoria de titulares.
 *  c) Programas de carácter temporal → máx. 3 años (+12 meses por ley FP).
 *  d) Exceso/acumulación de tareas → máx. 9 meses en periodo de 18.
 * Selección: principios de igualdad, mérito, capacidad, publicidad y CELERIDAD.
 * Nombramiento NO reconoce condición de FC.
 * Causas de fin de interinidad (además art. 63): cobertura reglada, razones
 * organizativas, fin del plazo, fin de la causa. */
enum class InterimCause : uint8_t {
    A_VACANT_POST_NO_FC          = 0,  // máx. 3 años
    B_TRANSIENT_SUBSTITUTION     = 1,
    C_TEMPORAL_PROGRAM           = 2,  // máx. 3 años (+12 meses)
    D_TASK_OVERLOAD              = 3,  // máx. 9 meses en 18
};
struct InterimLimits {
    static constexpr uint8_t MAX_YEARS_VACANT          = 3;   // ⭐
    static constexpr uint8_t MAX_YEARS_PROGRAM         = 3;
    static constexpr uint8_t PROGRAM_EXTENSION_MONTHS  = 12;
    static constexpr uint8_t MAX_MONTHS_OVERLOAD       = 9;   // ⭐
    static constexpr uint8_t OVERLOAD_WINDOW_MONTHS    = 18;
};

/* art. 11 — Personal laboral
 * Contrato de trabajo escrito; modalidades laborales vigentes.
 * Selección: igualdad, mérito, capacidad; temporal además celeridad. */
/* art. 12 — Personal eventual
 * Nombramiento no permanente; solo funciones de CONFIANZA O ASESORAMIENTO ESPECIAL.
 * Nombramiento y cese: LIBRES. Cese automático con la autoridad que lo nombró.
 * Su condición NO puede constituir mérito para acceso a FP ni promoción interna. */
struct EventualStaff {
    static constexpr bool FREE_APPOINTMENT_DISMISSAL   = true;  // ⭐
    static constexpr bool COUNTS_AS_MERIT              = false; // ⭐ NO es mérito
};

// ---- Título III, Cap. I — Derechos individuales ----

/* art. 14 — Derechos individuales de los empleados públicos — ⭐ VIP */
enum class IndividualRight : uint8_t {
    A_IMMOVABILITY_FC            = 0,   // inamovilidad (solo FC)
    B_EFFECTIVE_PERFORMANCE      = 1,
    C_CAREER_PROGRESSION         = 2,   // carrera y promoción interna
    D_RETRIBUTIONS_INDEMNITIES   = 3,
    E_PARTICIPATE_OBJECTIVES     = 4,
    F_LEGAL_DEFENCE              = 5,
    G_CONTINUOUS_TRAINING        = 6,   // preferentemente en horario laboral
    H_DIGNITY_PRIVACY_HARASSMENT = 7,   // intimidad, identidad, acoso
    I_NON_DISCRIMINATION         = 8,
    J_WORK_LIFE_BALANCE          = 9,
    J_BIS_DIGITAL_PRIVACY        = 10,  // dispositivos digitales, desconexión ⭐
    K_FREEDOM_OF_EXPRESSION      = 11,
    L_HEALTH_SAFETY              = 12,
    M_VACATIONS_PERMITS          = 13,
    N_RETIREMENT                 = 14,
    O_SOCIAL_SECURITY            = 15,
    P_FREE_PROFESSIONAL_ASSOC    = 16,
    Q_OTHER_LEGAL_RIGHTS         = 17,
};

/* art. 15 — Derechos individuales ejercidos colectivamente — ⭐ VIP */
enum class CollectiveRight : uint8_t {
    A_UNION_FREEDOM              = 0,
    B_COLLECTIVE_BARGAINING      = 1,
    C_STRIKE_ESSENTIAL_SERVICES  = 2,  // con garantía de servicios esenciales
    D_COLLECTIVE_DISPUTES        = 3,
    E_MEETING_RIGHT              = 4,  // art. 46
};

// ---- Título III, Cap. II — Carrera profesional ----

/* art. 16 — Concepto y modalidades de carrera profesional — ⭐ VIP
 * La carrera profesional: conjunto ordenado de oportunidades de ascenso y
 * expectativas de progreso conforme a igualdad, mérito y capacidad.
 * Modalidades posibles (aisladas o simultáneas): */
enum class CareerModality : uint8_t {
    A_HORIZONTAL = 0,  // progresión de grado/cat./escalón sin cambio de puesto ⭐
    B_VERTICAL   = 1,  // ascenso en estructura de puestos (provisión Cap. III T. V)
    C_INTERNAL_VERTICAL_PROMO  = 2,  // ascenso a Subgrupo superior (art. 18)
    D_INTERNAL_HORIZONTAL_PROMO = 3, // acceso a cuerpos del mismo Subgrupo (art. 18)
};

/* art. 18 — Promoción interna de FC — requisitos
 * Procesos selectivos: igualdad, mérito, capacidad (art. 55.2).
 * Requisito mínimo: ANTIGÜEDAD DE 2 AÑOS en servicio activo en el inferior Subgrupo. */
struct InternalPromotion {
    static constexpr uint8_t MIN_SENIORITY_YEARS = 2;  // ⭐
};

/* art. 20 — Evaluación del desempeño — ⭐ VIP
 * Procedimiento para medir/valorar conducta profesional y rendimiento/logros.
 * Criterios: transparencia, objetividad, imparcialidad, no discriminación.
 * Efectos: carrera horizontal, formación, provisión de puestos, retribuciones
 * complementarias (art. 24 c). Continuidad en puesto por concurso vinculada
 * a evaluación del desempeño (con audiencia y resolución motivada). */
struct PerformanceEvaluation {
    static constexpr bool TRANSPARENCY        = true;
    static constexpr bool OBJECTIVITY         = true;
    static constexpr bool IMPARTIALITY        = true;
    static constexpr bool NON_DISCRIMINATION  = true;
};

// ---- Título III, Cap. III — Retribuciones ----

/* art. 22 — Retribuciones de los funcionarios de carrera — ⭐ VIP
 * Clasificación: básicas + complementarias.
 * BÁSICAS: retribuyen adscripción al Subgrupo y antigüedad (sueldo + trienios).
 * COMPLEMENTARIAS: retribuyen características del puesto, carrera o desempeño.
 * Pagas extraordinarias: 2 al año, cada una = 1 mensualidad (básicas + complementarias,
 * salvo las de art. 24 c y d). */
struct Retributions {
    static constexpr uint8_t EXTRA_PAYMENTS_PER_YEAR  = 2;  // ⭐
};

/* art. 23 — Retribuciones básicas (fijadas en LPGE)
 *  a) Sueldo: asignado a cada Subgrupo/Grupo.
 *  b) Trienios: cantidad igual por Subgrupo/Grupo por cada 3 años de servicio. */
struct BasicRetributions {
    static constexpr uint8_t TRIENNIUM_YEARS = 3;  // ⭐
};

/* art. 24 — Retribuciones complementarias — factores:
 *  a) Progresión en carrera administrativa.
 *  b) Especial dificultad, responsabilidad, dedicación, incompatibilidad o condiciones.
 *  c) Grado de interés, iniciativa, rendimiento o resultados (vinculado a evaluación).
 *  d) Servicios extraordinarios fuera de jornada normal. */
enum class ComplementaryFactor : uint8_t {
    A_CAREER_PROGRESS            = 0,
    B_DIFFICULTY_RESPONSIBILITY  = 1,
    C_PERFORMANCE_RESULTS        = 2,  // vinculado a evaluación desempeño ⭐
    D_OVERTIME_EXTRAORDINARY     = 3,
};

// ---- Título III, Cap. IV — Representación ----

/* art. 39.5 — Composición de las Juntas de Personal — ⭐ VIP
 * Escala de representantes por número de funcionarios en la unidad electoral: */
struct PersonnelBoardScale {
    //  [min, max, num_reps]
    static constexpr uint8_t SCALE_50_100    = 5;
    static constexpr uint8_t SCALE_101_250   = 9;
    static constexpr uint8_t SCALE_251_500   = 13;
    static constexpr uint8_t SCALE_501_750   = 17;
    static constexpr uint8_t SCALE_751_1000  = 21;
    static constexpr uint8_t SCALE_1001_STEP = 2;   // 2 por cada 1.000 o fracción
    static constexpr uint8_t SCALE_MAX       = 75;
};

/* Delegados de Personal (art. 39.2):
 * Unidades: 6 ≤ funcionarios < 50.
 *  ≤ 30 → 1 delegado; 31-49 → 3 delegados (mancomunadamente). */
struct PersonnelDelegates {
    static constexpr uint8_t THRESHOLD_LOWER   = 6;
    static constexpr uint8_t THRESHOLD_BOARD   = 50;   // Juntas desde 50
    static constexpr uint8_t DELEGATES_1_LIMIT = 30;   // hasta 30 → 1 delegado
    static constexpr uint8_t DELEGATES_3       = 3;    // 31-49 → 3 delegados
};

/* art. 41.1.d — Crédito horario mensual de representantes — ⭐ VIP
 * Escala de horas mensuales retribuidas dentro de jornada: */
struct RepHoursCredit {
    static constexpr uint8_t UP_TO_100     = 15;
    static constexpr uint8_t FROM_101_250  = 20;
    static constexpr uint8_t FROM_251_500  = 30;
    static constexpr uint8_t FROM_501_750  = 35;
    static constexpr uint8_t FROM_751_UP   = 40;
};

// ---- Título III, Cap. V — Permisos y vacaciones ----

/* art. 47 bis — Teletrabajo — ⭐ VIP
 * Prestación a distancia usando TIC, siempre que las necesidades del servicio
 * lo permitan. Debe ser expresamente AUTORIZADO y es compatible con presencial.
 * Tiene carácter VOLUNTARIO Y REVERSIBLE (salvo supuestos excepcionales).
 * Mismos derechos y deberes que el personal presencial.
 * La Administración proporciona y mantiene los medios tecnológicos. */
struct Telework {
    static constexpr bool VOLUNTARY          = true;   // ⭐
    static constexpr bool REVERSIBLE         = true;   // ⭐
    static constexpr bool REQUIRES_AUTH      = true;
    static constexpr bool SAME_RIGHTS_DUTIES = true;
    static constexpr bool ADMIN_PROVIDES_TECH = true;
};

/* art. 48 — Permisos clave (selección):
 *  a) Accidente/enfermedad/hospitalización: 5 días hábiles (1.er grado)
 *                                            4 días hábiles (2.º grado)
 *     Fallecimiento 1.er grado: 3 d.h. (misma localidad) / 5 d.h. (distinta)
 *     Fallecimiento 2.º grado: 2 d.h. (misma) / 4 d.h. (distinta)
 *  b) Traslado de domicilio sin cambio residencia: 1 día.
 *  f) Lactancia hijo < 12 meses: 1 hora al día (divisible en 2 fracciones).
 *  k) Asuntos particulares: 6 días al año.
 *  l) Matrimonio / pareja de hecho formalizada: 15 días. */
struct Permits {
    static constexpr uint8_t HOSP_FIRST_DEGREE_DAYS      = 5;  // ⭐
    static constexpr uint8_t HOSP_SECOND_DEGREE_DAYS     = 4;
    static constexpr uint8_t DEATH_FIRST_SAME_LOCALITY   = 3;
    static constexpr uint8_t DEATH_FIRST_OTHER_LOCALITY  = 5;
    static constexpr uint8_t DEATH_SECOND_SAME_LOCALITY  = 2;
    static constexpr uint8_t DEATH_SECOND_OTHER_LOCALITY = 4;
    static constexpr uint8_t RELOCATION_DAYS             = 1;
    static constexpr uint8_t PERSONAL_AFFAIRS_DAYS       = 6;  // ⭐
    static constexpr uint8_t MARRIAGE_DAYS               = 15; // ⭐
    static constexpr uint8_t BREASTFEEDING_HOURS_PER_DAY = 1;
    static constexpr uint8_t BREASTFEEDING_MAX_AGE_MONTHS = 12;
};

/* art. 50 — Vacaciones
 * 22 días hábiles por año natural (los sábados NO cuentan como hábiles).
 * Si hay permiso de maternidad/IT/riesgo durante el año, se puede disfrutar
 * hasta 18 meses después de finalizar el año en que se generaron.
 * NO pueden sustituirse por cuantía económica (salvo conclusión de servicios
 * ajena a la voluntad del funcionario: máx. 18 meses de compensación). */
struct Vacations {
    static constexpr uint8_t  WORKING_DAYS_PER_YEAR      = 22;  // ⭐
    static constexpr bool     SATURDAY_IS_WORKING_DAY    = false;
    static constexpr uint8_t  CARRYOVER_MONTHS_MAX       = 18;  // ⭐
};

// ---- Título III, Cap. VI — Deberes y Código de Conducta ----

/* art. 52 — Código de Conducta — principios rectores */
static constexpr const char* CONDUCT_PRINCIPLES[] = {
    "objetividad", "integridad", "neutralidad", "responsabilidad",
    "imparcialidad", "confidencialidad", "dedicación al servicio público",
    "transparencia", "ejemplaridad", "austeridad", "accesibilidad",
    "eficacia", "honradez", "promoción del entorno cultural y medioambiental",
    "respeto a la igualdad entre mujeres y hombres"
};

// ---- Título VI — Situaciones administrativas ----

/* art. 85 — Situaciones de los funcionarios de carrera — ⭐ VIP */
enum class AdminSituation : uint8_t {
    A_ACTIVE_SERVICE             = 0,  // servicio activo
    B_SPECIAL_SERVICES           = 1,  // servicios especiales
    C_OTHER_PUBLIC_ADMIN         = 2,  // servicio en otras AAPP
    D_LEAVE                      = 3,  // excedencia
    E_SUSPENDED                  = 4,  // suspensión de funciones
};

/* art. 87 — Servicios especiales — causas habilitantes (selección) — ⭐ VIP
 * Los FC son declarados en servicios especiales cuando:
 *  a) Son designados miembros del Gobierno/CCAA/UE/org. internacionales o altos cargos.
 *  b) Autorizados para misión > 6 meses en org. internacionales/gobiernos extranjeros.
 *  c) Nombrados para puestos asimilados a altos cargos en organismos públicos.
 *  d) Adscritos al TC, Defensor del Pueblo o Tribunal de Cuentas.
 *  e) Diputado/Senador o miembro de asamblea legislativa CCAA con retribución periódica.
 *  f) Cargos electivos retribuidos de dedicación exclusiva en EELL.
 *  g) Designados para el CGPJ o consejos de justicia CCAA.
 *  h) Elegidos para Órganos Constitucionales/estatutarios o cuya elección corresponda
 *     al Congreso, Senado o asambleas legislativas.
 *  i-l) Personal eventual político, org. internacionales, asesores parlamentarios,
 *       reservistas voluntarios FFAA.
 * EFECTOS: perciben retribuciones del cargo (no del cuerpo), PERO se les computa
 * el tiempo a efectos de ascensos, trienios, promoción interna y Seguridad Social.
 * Derecho de reingreso garantizado en la misma localidad con retribuciones de la
 * categoría/nivel/escalón consolidados. */
enum class SpecialServicesCause : uint8_t {
    A_GOVERNMENT_MEMBER          = 0,
    B_INTERNATIONAL_MISSION      = 1,  // > 6 meses
    C_ASSIMILATED_HIGH_OFFICER   = 2,
    D_TC_DP_TRIBUNAL_CUENTAS     = 3,
    E_CONGRESS_SENATOR_CCAA      = 4,  // ⭐
    F_LOCAL_ELECTED_EXCLUSIVE    = 5,
    G_CGPJ_JUSTICE_COUNCILS      = 6,
    H_CONSTITUTIONAL_BODIES      = 7,
    I_EVENTUAL_POLITICAL         = 8,
    J_INT_ORGANIZATIONS          = 9,
    K_PARLIAMENTARY_ADVISER      = 10,
    L_MILITARY_VOLUNTEER_RESERVE = 11,
};

/* art. 89 — Excedencia — modalidades — ⭐ VIP */
enum class LeaveModality : uint8_t {
    A_VOLUNTARY_PERSONAL_INTEREST = 0,  // req. 5 años servicio efectivo ⭐
    B_VOLUNTARY_FAMILY_GROUPING   = 1,  // sin req. de servicios mínimos
    C_FAMILY_CARE                 = 2,  // máx. 3 años por hijo/familiar ⭐
    D_GENDER_VIOLENCE             = 3,  // sin mínimo de servicios previos ⭐
    E_TERRORIST_VIOLENCE          = 4,
};

struct LeaveRequirements {
    static constexpr uint8_t PERSONAL_MIN_YEARS         = 5;   // ⭐ excedencia vol. int. particular
    static constexpr uint8_t FAMILY_CARE_MAX_YEARS      = 3;   // ⭐
    static constexpr uint8_t POST_RESERVATION_MONTHS    = 24;  // reserva del puesto 2 años
    static constexpr uint8_t GENDER_VIOLENCE_RESERVE_MONTHS = 6;
    static constexpr uint8_t GENDER_VIOLENCE_PAID_MONTHS    = 2;  // retribuciones íntegras
};

/* art. 90 — Suspensión de funciones
 * Privación del ejercicio de funciones y derechos; pérdida del puesto si > 6 meses.
 * Suspensión firme: por sentencia criminal o sanción disciplinaria (máx. 6 años).
 * Durante la suspensión NO puede prestar servicios en ninguna AAPP. */
struct FunctionSuspension {
    static constexpr uint8_t POST_LOSS_IF_EXCEEDS_MONTHS = 6;  // ⭐
    static constexpr uint8_t MAX_DISCIPLINARY_YEARS       = 6;  // ⭐
};

// ---- Título VII — Régimen disciplinario ----

/* art. 96 — Sanciones disciplinarias */
enum class DisciplinarySanction : uint8_t {
    A_SEPARATION_FROM_SERVICE    = 0,  // solo faltas muy graves (FC)
    B_LABOUR_DISMISSAL           = 1,  // solo faltas muy graves (personal laboral)
    C_FUNCTION_SUSPENSION        = 2,  // máx. 6 años
    D_FORCED_TRANSFER            = 3,
    E_DEMERIT                    = 4,  // penalización carrera/promoción
    F_WARNING                    = 5,
    G_OTHER_LEGAL                = 6,
};

/* art. 97 — Prescripción de faltas y sanciones TREBEP — ⭐⭐⭐ VIP MÁXIMO
 * ATENCIÓN: diferente de art. 32 Ley 19/2013 (buen gobierno):
 *   FALTAS:     muy graves → 3 años; graves → 2 años; leves → 6 meses.
 *   SANCIONES:  muy graves → 3 años; graves → 2 años; leves → 1 año.
 * El plazo de las FALTAS comienza desde su comisión (o cese si continuadas).
 * El plazo de las SANCIONES comienza desde la firmeza de la resolución. */
struct DisciplinaryPrescription {
    // Faltas
    static constexpr uint8_t FAULT_VERY_SERIOUS_YEARS = 3;  // ⭐ (NO 5 como en buen gob.)
    static constexpr uint8_t FAULT_SERIOUS_YEARS       = 2;  // ⭐
    static constexpr uint8_t FAULT_MINOR_MONTHS        = 6;  // ⭐
    // Sanciones
    static constexpr uint8_t SANC_VERY_SERIOUS_YEARS  = 3;
    static constexpr uint8_t SANC_SERIOUS_YEARS        = 2;
    static constexpr uint8_t SANC_MINOR_YEARS          = 1;  // ⭐ (sanciones leves → 1 AÑO)
};

// ---- RD 364/1995 — Provisión de puestos de trabajo ----

/* art. 36 — Formas de provisión (Título III, RD 364/1995)
 * Sistema normal: CONCURSO.
 * Excepcionalmente: libre designación (según RPT).
 * Si exige el servicio: redistribución o reasignación de efectivos (Plan Empleo).
 * Temporalmente: comisión de servicios y adscripción provisional. */
enum class ProvisionMethod : uint8_t {
    CONCURSO                     = 0,  // sistema normal ⭐
    LIBRE_DESIGNACION            = 1,
    REDISTRIBUCION_EFECTIVOS     = 2,
    REASIGNACION_EFECTIVOS       = 3,
    COMISION_SERVICIOS           = 4,  // temporal
    ADSCRIPCION_PROVISIONAL      = 5,  // temporal
};

/* art. 37 — Anotaciones en el Registro Central de Personal
 * Diligencias de cese y toma de posesión: comunicar al RCP en 3 días hábiles. */
struct PersonnelRegistry {
    static constexpr uint8_t COMMUNICATION_DAYS = 3;  // ⭐
};

/* art. 42.2 — Plazo de presentación de instancias en concurso
 * 15 días hábiles desde la publicación en el BOE. */
struct ConcursoDeadlines {
    static constexpr uint8_t APPLICATION_WORKING_DAYS = 15;  // ⭐
};

/* art. 44 — Méritos valorables en concurso:
 *  b) Grado personal consolidado.
 *  c) Valoración del trabajo desarrollado.
 *  d) Cursos de formación y perfeccionamiento.
 *  e) Antigüedad (computando servicios previos a FC; no simultáneos).
 * Puntuación específica (familia, cuidado hijos): máx. lo mismo que antigüedad;
 * límite: no puede exceder el 40 % ni ser inferior al 10 % de puntuación máxima. */
struct ConcursoMerits {
    static constexpr float SPECIAL_MERIT_MAX_PCT = 0.40f;  // ⭐
    static constexpr float SPECIAL_MERIT_MIN_PCT = 0.10f;  // ⭐
};

/* art. 46 — Comisiones de Valoración (concurso)
 * Mínimo 4 miembros; al menos uno propuesto por el centro directivo de personal.
 * Sindicatos más representativos (y los > 10 % representación) participan como
 * miembros, pero su número < miembros designados por la Administración.
 * Miembros: grupo de titulación igual o superior al exigido para el puesto.
 * Presidentes y Secretarios: nombrados por la autoridad convocante entre los
 * miembros de la Administración. */
struct ValuationCommission {
    static constexpr uint8_t MIN_MEMBERS = 4;  // ⭐
};

/* art. 47 — Plazo de resolución del concurso: 2 meses desde fin plazo solicitudes. */
struct ConcursoResolution {
    static constexpr uint8_t RESOLUTION_MONTHS = 2;  // ⭐
};

/* art. 48 — Toma de posesión
 * Sin cambio de residencia: 3 días hábiles.
 * Con cambio de residencia o reingreso: 1 mes.
 * El Subsecretario puede diferir el cese hasta 20 días hábiles por necesidades.
 * Excepcionalmente (Secretaría de Estado): hasta 3 meses adicionales. */
struct Possession {
    static constexpr uint8_t WORKING_DAYS_NO_RELOC  = 3;  // ⭐
    static constexpr uint8_t MONTHS_WITH_RELOC       = 1;  // ⭐
    static constexpr uint8_t SUBSECRETORY_DEFER_DAYS = 20;
    static constexpr uint8_t MAX_DEFER_MONTHS        = 3;
};

/* art. 51 — Libre designación: puestos elegibles
 * Solo: Subdirector general, Delegados y Directores territoriales/provinciales/
 * Comisionados, Secretarías de Altos Cargos y otros directivos/especial
 * responsabilidad determinados en las RPT.
 * Cese: discrecional. FC cesado → adscripción provisional en puesto
 * no inferior en > 2 niveles al grado personal, mismo municipio. */
struct FreeDesignation {
    static constexpr bool DISMISSAL_DISCRETIONAL    = true;  // ⭐
    static constexpr uint8_t REASSIGNMENT_LEVEL_GAP = 2;    // máx. 2 niveles inferior
};

/* art. 56 — Plazos en libre designación
 * Nombramiento: máx. 1 mes desde fin presentación solicitudes (+1 mes prórroga). */
struct FreeDesignationDeadlines {
    static constexpr uint8_t APPOINTMENT_MONTHS     = 1;  // ⭐
    static constexpr uint8_t EXTENSION_MONTHS       = 1;
};

/* art. 70 — Grado personal (Título IV, RD 364/1995)
 * Los puestos de trabajo se clasifican en 30 NIVELES.
 * FC adquieren grado personal por desempeño de puesto del nivel correspondiente
 * durante 2 años CONTINUADOS o 3 con interrupción.
 * Si el puesto es > 2 niveles al grado personal: consolidan grado superior en
 * 2 niveles cada 2 años continuados (sin superar el del puesto desempeñado). */
struct PersonalGrade {
    static constexpr uint8_t TOTAL_LEVELS          = 30;   // ⭐
    static constexpr uint8_t CONSOLIDATION_CONT_YRS = 2;   // ⭐
    static constexpr uint8_t CONSOLIDATION_INT_YRS  = 3;   // ⭐ con interrupción
    static constexpr uint8_t FAST_TRACK_LEVEL_JUMP  = 2;
};

/* art. 71 — Intervalos de niveles por Grupo — ⭐ VIP
 *   Grupo A: 20-30 | Grupo B: 16-26 | Grupo C: 11-22
 *   Grupo D:  9-18 | Grupo E:  7-14 */
struct LevelIntervals {
    //  { min, max }
    static constexpr uint8_t GROUP_A_MIN = 20;  // ⭐
    static constexpr uint8_t GROUP_A_MAX = 30;
    static constexpr uint8_t GROUP_B_MIN = 16;
    static constexpr uint8_t GROUP_B_MAX = 26;
    static constexpr uint8_t GROUP_C_MIN = 11;
    static constexpr uint8_t GROUP_C_MAX = 22;
    static constexpr uint8_t GROUP_D_MIN =  9;
    static constexpr uint8_t GROUP_D_MAX = 18;
    static constexpr uint8_t GROUP_E_MIN =  7;
    static constexpr uint8_t GROUP_E_MAX = 14;
};

/* Promoción interna (Título V, RD 364/1995)
 * art. 73: Consiste en el ascenso desde Cuerpos/Escalas de un Grupo a otro
 * inmediato superior, o acceso a Cuerpos/Escalas del mismo Grupo.
 * art. 74: Sistemas: oposición o CONCURSO-OPOSICIÓN (igualdad, mérito, cap., publicidad).
 *   En concurso-oposición: puntuación del concurso NO se aplica para superar oposición.
 * art. 76: Requisito: antigüedad mínima de 2 años en el Cuerpo/Escala + titulación. */
struct InternalPromotionRD364 {
    static constexpr uint8_t MIN_SENIORITY_BODY_YEARS = 2;  // ⭐
    static constexpr bool    CONCURSO_SCORE_EXEMPT     = true; // no sirve para superar opos.
};

} // namespace workforce_mgr

#endif // CIVIL_SERVICE_POLICY_HPP
