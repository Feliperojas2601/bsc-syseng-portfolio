
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class Sintactic {

    public ArrayList<Token> tokens;
    public Token currentToken;
    public GrammarRule currentGrammarRule;
    public ArrayList<GrammarRule> grammar = new ArrayList<GrammarRule>();
    public ArrayList<String> reviewedRules = new ArrayList<String>();
    public boolean goToGrammarRule = true;

    Sintactic (ArrayList<Token> tokens) {
        this.tokens = tokens;
        this.setGrammar();
        this.setPredictions();
        this.currentToken = this.tokens.get(0);
        this.currentGrammarRule = this.grammar.get(0);
        boolean errorMainProcess = true;
        for (Token token : this.tokens){
            if(token.type.equals("proceso") || token.type.equals("algoritmo")) {
                errorMainProcess = false;
                break;
            }
        }
        if (errorMainProcess) {
            System.out.println("Error sintactico: falta proceso");
        } else {
            if (this.recursiveProcessTokens(this.currentGrammarRule.rule)) {
                System.out.println("El analisis sintactico ha finalizado exitosamente.");
            };
        }
    }

    void setGrammar () {
        ArrayList<String> rightpart = new ArrayList<String>();
        rightpart.add("FUNCION");
        rightpart.add("PROCESO");
        rightpart.add("FUNCION");
        this.grammar.add(new GrammarRule("S",rightpart));
        rightpart.clear();
        rightpart.add("PROCESO_FUNCION");
        rightpart.add("FUNCION");
        this.grammar.add(new GrammarRule("FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("epsilon");
        this.grammar.add(new GrammarRule("FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("INICIO_PROCESO_FUNCION");
        rightpart.add("id");
        rightpart.add("DESCRIPCION_FUNCION");
        rightpart.add("BLOQUE_PROCESO_FUNCION");
        this.grammar.add(new GrammarRule("PROCESO_FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("funcion");
        this.grammar.add(new GrammarRule("INICIO_PROCESO_FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("subproceso");
        this.grammar.add(new GrammarRule("INICIO_PROCESO_FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("BLOQUE");
        rightpart.add("FIN_PROCESO_FUNCION");
        this.grammar.add(new GrammarRule("BLOQUE_PROCESO_FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("SI");
        rightpart.add("BLOQUE");
        this.grammar.add(new GrammarRule("BLOQUE",rightpart));
        rightpart.clear();
        rightpart.add("PARA");
        rightpart.add("BLOQUE");
        this.grammar.add(new GrammarRule("BLOQUE",rightpart));
        rightpart.clear();
        rightpart.add("MIENTRAS");
        rightpart.add("BLOQUE");
        this.grammar.add(new GrammarRule("BLOQUE",rightpart));
        rightpart.clear();
        rightpart.add("REPETIR");
        rightpart.add("BLOQUE");
        this.grammar.add(new GrammarRule("BLOQUE",rightpart));
        rightpart.clear();
        rightpart.add("DECLARACION");
        rightpart.add("BLOQUE");
        this.grammar.add(new GrammarRule("BLOQUE",rightpart));
        rightpart.clear();
        rightpart.add("ASIGNAR");
        rightpart.add("BLOQUE");
        this.grammar.add(new GrammarRule("BLOQUE",rightpart));
        rightpart.clear();
        rightpart.add("SEGUN");
        rightpart.add("BLOQUE");
        this.grammar.add(new GrammarRule("BLOQUE",rightpart));
        rightpart.clear();
        rightpart.add("ACCION_NO_RECURSIVA");
        rightpart.add("BLOQUE");
        this.grammar.add(new GrammarRule("BLOQUE",rightpart));
        rightpart.clear();
        rightpart.add("epsilon");
        this.grammar.add(new GrammarRule("BLOQUE",rightpart));
        rightpart.clear();
        rightpart.add("DIMENSION");
        rightpart.add("BLOQUE");
        this.grammar.add(new GrammarRule("BLOQUE",rightpart));
        rightpart.clear();
        rightpart.add("si");
        rightpart.add("EXPRESION");
        rightpart.add("entonces");
        rightpart.add("BLOQUE_SI");
        this.grammar.add(new GrammarRule("SI",rightpart));
        rightpart.clear();
        rightpart.add("BLOQUE");
        rightpart.add("SI_VARIANTE_1");
        this.grammar.add(new GrammarRule("BLOQUE_SI",rightpart));
        rightpart.clear();
        rightpart.add("sino");
        rightpart.add("BLOQUE_SI_VARIANTE_1");
        this.grammar.add(new GrammarRule("SI_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("finsi");
        this.grammar.add(new GrammarRule("SI_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("BLOQUE");
        rightpart.add("finsi");
        this.grammar.add(new GrammarRule("BLOQUE_SI_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("para");
        rightpart.add("id");
        rightpart.add("token_asig");
        rightpart.add("EXPRESION");
        rightpart.add("hasta");
        rightpart.add("EXPRESION");
        rightpart.add("PARA_VARIANTE_1");
        this.grammar.add(new GrammarRule("PARA",rightpart));
        rightpart.clear();
        rightpart.add("con");
        rightpart.add("paso");
        rightpart.add("EXPRESION");
        rightpart.add("hacer");
        rightpart.add("BLOQUE_PARA");
        this.grammar.add(new GrammarRule("PARA_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("hacer");
        rightpart.add("BLOQUE_PARA");
        this.grammar.add(new GrammarRule("PARA_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("BLOQUE");
        rightpart.add("finpara");
        this.grammar.add(new GrammarRule("BLOQUE_PARA",rightpart));
        rightpart.clear();
        rightpart.add("mientras");
        rightpart.add("EXPRESION");
        rightpart.add("hacer");
        rightpart.add("BLOQUE_MIENTRAS");
        this.grammar.add(new GrammarRule("MIENTRAS",rightpart));
        rightpart.clear();
        rightpart.add("BLOQUE");
        rightpart.add("finmientras");
        this.grammar.add(new GrammarRule("BLOQUE_MIENTRAS",rightpart));
        rightpart.clear();
        rightpart.add("definir");
        rightpart.add("LISTA_DE_DEFINIR_ID");
        rightpart.add("como");
        rightpart.add("TIPO");
        rightpart.add("token_pyc");
        this.grammar.add(new GrammarRule("DECLARACION",rightpart));
        rightpart.clear();
        rightpart.add("id");
        rightpart.add("ASIGNAR_VARIANTE_1_INTERMEDIA");
        this.grammar.add(new GrammarRule("ASIGNAR",rightpart));
        rightpart.clear();
        rightpart.add("ASIGNAR_VARIANTE_1");
        this.grammar.add(new GrammarRule("ASIGNAR_VARIANTE_1_INTERMEDIA",rightpart));
        rightpart.clear();
        rightpart.add("ASIGNACION_VARIANTE_1");
        this.grammar.add(new GrammarRule("ASIGNAR_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("IDR_SIN_ASIGNACION");
        rightpart.add("token_pyc");
        this.grammar.add(new GrammarRule("ASIGNAR_VARIANTE_1",rightpart));

        rightpart.clear();
        rightpart.add("id");
        rightpart.add("ASIGNACION_VARIANTE_1");
        this.grammar.add(new GrammarRule("ASIGNACION",rightpart));
        rightpart.clear();
        rightpart.add("token_cor_izq");
        rightpart.add("LISTA_DE_EXPRESIONES");
        rightpart.add("token_cor_der");
        rightpart.add("token_asig");
        rightpart.add("EXPRESION");
        rightpart.add("token_pyc");
        this.grammar.add(new GrammarRule("ASIGNACION_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("token_asig");
        rightpart.add("EXPRESION");
        rightpart.add("token_pyc");
        this.grammar.add(new GrammarRule("ASIGNACION_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("dimension");
        rightpart.add("id");
        rightpart.add("DIMENSIONAR");
        rightpart.add("DIMENSION_VARIANTE_1");
        rightpart.add("token_pyc");
        this.grammar.add(new GrammarRule("DIMENSION",rightpart));
        rightpart.clear();
        rightpart.add("token_coma");
        rightpart.add("id");
        rightpart.add("DIMENSIONAR");
        rightpart.add("DIMENSION_VARIANTE_1");
        this.grammar.add(new GrammarRule("DIMENSION_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("epsilon");
        this.grammar.add(new GrammarRule("DIMENSION_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("segun");
        rightpart.add("EXPRESION");
        rightpart.add("hacer");
        rightpart.add("LISTA_DE_CASO");
        this.grammar.add(new GrammarRule("SEGUN",rightpart));
        rightpart.clear();
        rightpart.add("finsegun");
        this.grammar.add(new GrammarRule("SEGUN_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("de");
        rightpart.add("otro");
        rightpart.add("modo");
        rightpart.add("token_dosp");
        rightpart.add("BLOQUE_SEGUN_VARIANTE_1");
        this.grammar.add(new GrammarRule("SEGUN_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("BLOQUE");
        rightpart.add("finsegun");
        this.grammar.add(new GrammarRule("BLOQUE_SEGUN_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("caso");
        rightpart.add("EXPRESION");
        rightpart.add("token_dosp");
        rightpart.add("BLOQUE_LISTA_DE_CASO");
        this.grammar.add(new GrammarRule("LISTA_DE_CASO",rightpart));
        rightpart.clear();
        rightpart.add("SEGUN_VARIANTE_1");
        this.grammar.add(new GrammarRule("LISTA_DE_CASO",rightpart));
        rightpart.clear();
        rightpart.add("BLOQUE");
        rightpart.add("LISTA_DE_CASO");
        this.grammar.add(new GrammarRule("BLOQUE_LISTA_DE_CASO",rightpart));
        rightpart.clear();
        rightpart.add("borrar");
        rightpart.add("pantalla");
        rightpart.add("token_pyc");
        this.grammar.add(new GrammarRule("ACCION_NO_RECURSIVA",rightpart));
        rightpart.clear();
        rightpart.add("ESCRIBIR");
        this.grammar.add(new GrammarRule("ACCION_NO_RECURSIVA",rightpart));
        rightpart.clear();
        rightpart.add("ESPERAR");
        this.grammar.add(new GrammarRule("ACCION_NO_RECURSIVA",rightpart));
        rightpart.clear();
        rightpart.add("LEER");
        this.grammar.add(new GrammarRule("ACCION_NO_RECURSIVA",rightpart));
        rightpart.clear();
        rightpart.add("limpiar");
        rightpart.add("pantalla");
        rightpart.add("token_pyc");
        this.grammar.add(new GrammarRule("ACCION_NO_RECURSIVA",rightpart));
        rightpart.clear();
        rightpart.add("repetir");
        rightpart.add("BLOQUE_REPETIR");
        this.grammar.add(new GrammarRule("REPETIR",rightpart));
        rightpart.clear();
        rightpart.add("BLOQUE");
        rightpart.add("hasta");
        rightpart.add("que");
        rightpart.add("EXPRESION");
        this.grammar.add(new GrammarRule("BLOQUE_REPETIR",rightpart));
        rightpart.clear();
        rightpart.add("EXPRESION");
        rightpart.add("LISTA_DE_EXPRESIONES_VARIANTE_1");
        this.grammar.add(new GrammarRule("LISTA_DE_EXPRESIONES",rightpart));
        rightpart.clear();
        rightpart.add("token_coma");
        rightpart.add("EXPRESION");
        rightpart.add("LISTA_DE_EXPRESIONES_VARIANTE_1");
        this.grammar.add(new GrammarRule("LISTA_DE_EXPRESIONES_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("epsilon");
        this.grammar.add(new GrammarRule("LISTA_DE_EXPRESIONES_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("id");
        rightpart.add("LISTA_DE_DEFINIR_ID_VARIANTE_1");
        this.grammar.add(new GrammarRule("LISTA_DE_DEFINIR_ID",rightpart));
        rightpart.clear();
        rightpart.add("token_coma");
        rightpart.add("id");
        rightpart.add("LISTA_DE_DEFINIR_ID_VARIANTE_1");
        this.grammar.add(new GrammarRule("LISTA_DE_DEFINIR_ID_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("epsilon");
        this.grammar.add(new GrammarRule("LISTA_DE_DEFINIR_ID_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("id");
        rightpart.add("LISTA_DE_LEER_ID_VARIANTE_1");
        this.grammar.add(new GrammarRule("LISTA_DE_LEER_ID",rightpart));
        rightpart.clear();
        rightpart.add("LISTA_DE_LEER_ID_VARIANTE_2");
        this.grammar.add(new GrammarRule("LISTA_DE_LEER_ID_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("epsilon");
        this.grammar.add(new GrammarRule("LISTA_DE_LEER_ID_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("DIMENSIONAR");
        rightpart.add("LISTA_DE_LEER_ID_VARIANTE_2");
        this.grammar.add(new GrammarRule("LISTA_DE_LEER_ID_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("LISTA_DE_LEER_ID_VARIANTE_3");
        this.grammar.add(new GrammarRule("LISTA_DE_LEER_ID_VARIANTE_2",rightpart));
        rightpart.clear();
        rightpart.add("epsilon");
        this.grammar.add(new GrammarRule("LISTA_DE_LEER_ID_VARIANTE_2",rightpart));
        rightpart.clear();
        rightpart.add("id");
        rightpart.add("LISTA_DE_LEER_ID_VARIANTE_2");
        this.grammar.add(new GrammarRule("LISTA_DE_LEER_ID_VARIANTE_3",rightpart));
        rightpart.clear();
        rightpart.add("id");
        rightpart.add("DIMENSIONAR");
        rightpart.add("LISTA_DE_LEER_ID_VARIANTE_2");
        this.grammar.add(new GrammarRule("LISTA_DE_LEER_ID_VARIANTE_3",rightpart));
        rightpart.clear();
        rightpart.add("epsilon");
        this.grammar.add(new GrammarRule("LISTA_DE_LEER_ID_VARIANTE_3",rightpart));
        rightpart.clear();
        rightpart.add("escribir");
        rightpart.add("LISTA_DE_EXPRESIONES");
        rightpart.add("token_pyc");
        this.grammar.add(new GrammarRule("ESCRIBIR",rightpart));
        rightpart.clear();
        rightpart.add("esperar");
        rightpart.add("ESPERAR_VARIANTE_1");
        this.grammar.add(new GrammarRule("ESPERAR",rightpart));
        rightpart.clear();
        rightpart.add("tecla");
        rightpart.add("token_pyc");
        this.grammar.add(new GrammarRule("ESPERAR_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("EXPRESION");
        rightpart.add("TIEMPO");
        rightpart.add("token_pyc");
        this.grammar.add(new GrammarRule("ESPERAR_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("segundos");
        this.grammar.add(new GrammarRule("TIEMPO",rightpart));
        rightpart.clear();
        rightpart.add("milisegundos");
        this.grammar.add(new GrammarRule("TIEMPO",rightpart));
        rightpart.clear();
        rightpart.add("leer");
        rightpart.add("LISTA_DE_LEER_ID");
        rightpart.add("token_pyc");
        this.grammar.add(new GrammarRule("LEER",rightpart));
        rightpart.clear();
        rightpart.add("TERMINO");
        rightpart.add("EXPRESION_VARIANTE_1");
        this.grammar.add(new GrammarRule("EXPRESION",rightpart));
        rightpart.clear();
        rightpart.add("OPERADOR");
        rightpart.add("TERMINO");
        rightpart.add("EXPRESION_VARIANTE_1");
        this.grammar.add(new GrammarRule("EXPRESION_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("epsilon");
        this.grammar.add(new GrammarRule("EXPRESION_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("TOKEN_TIPO");
        rightpart.add("LISTA_DE_TOKEN_TIPO");
        this.grammar.add(new GrammarRule("TERMINO",rightpart));
        rightpart.clear();
        rightpart.add("OPERADOR");
        rightpart.add("TOKEN_TIPO");
        rightpart.add("LISTA_DE_TOKEN_TIPO");
        this.grammar.add(new GrammarRule("LISTA_DE_TOKEN_TIPO",rightpart));
        rightpart.clear();
        rightpart.add("epsilon");
        this.grammar.add(new GrammarRule("LISTA_DE_TOKEN_TIPO",rightpart));
        rightpart.clear();
        rightpart.add("token_par_izq");
        rightpart.add("EXPRESION");
        rightpart.add("token_par_der");
        this.grammar.add(new GrammarRule("TOKEN_TIPO",rightpart));
        rightpart.clear();
        rightpart.add("IDR_PROCESO_FUNCION");
        this.grammar.add(new GrammarRule("TOKEN_TIPO",rightpart));
        rightpart.clear();
        rightpart.add("token_real");
        this.grammar.add(new GrammarRule("TOKEN_TIPO",rightpart));
        rightpart.clear();
        rightpart.add("token_entero");
        this.grammar.add(new GrammarRule("TOKEN_TIPO",rightpart));
        rightpart.clear();
        rightpart.add("token_cadena");
        this.grammar.add(new GrammarRule("TOKEN_TIPO",rightpart));
        rightpart.clear();
        rightpart.add("verdadero");
        this.grammar.add(new GrammarRule("TOKEN_TIPO",rightpart));
        rightpart.clear();
        rightpart.add("falso");
        this.grammar.add(new GrammarRule("TOKEN_TIPO",rightpart));
        rightpart.clear();
        rightpart.add("token_neg");
        rightpart.add("EXPRESION");
        this.grammar.add(new GrammarRule("TOKEN_TIPO",rightpart));
        rightpart.clear();
        rightpart.add("token_menos");
        rightpart.add("EXPRESION");
        this.grammar.add(new GrammarRule("TOKEN_TIPO",rightpart));
        rightpart.clear();
        rightpart.add("id");
        rightpart.add("IDR_SIN_ASIGNACION");
        this.grammar.add(new GrammarRule("IDR_PROCESO_FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("PARAMETROS_PROCESO_FUNCION");
        this.grammar.add(new GrammarRule("IDR_SIN_ASIGNACION",rightpart));
        rightpart.clear();
        rightpart.add("DIMENSIONAR");
        this.grammar.add(new GrammarRule("IDR_SIN_ASIGNACION",rightpart));
        rightpart.clear();
        rightpart.add("epsilon");
        this.grammar.add(new GrammarRule("IDR_SIN_ASIGNACION",rightpart));
        rightpart.clear();
        rightpart.add("token_par_izq");
        rightpart.add("LISTA_DE_PARAMETROS_PROCESO_FUNCION");
        rightpart.add("token_par_der");
        this.grammar.add(new GrammarRule("PARAMETROS_PROCESO_FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("token_cor_izq");
        rightpart.add("LISTA_DE_EXPRESIONES");
        rightpart.add("token_cor_der");
        this.grammar.add(new GrammarRule("DIMENSIONAR",rightpart));
        rightpart.clear();
        rightpart.add("EXPRESION");
        rightpart.add("LISTA_DE_PARAMETROS_PROCESO_FUNCION_VARIANTE_1");
        this.grammar.add(new GrammarRule("LISTA_DE_PARAMETROS_PROCESO_FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("epsilon");
        this.grammar.add(new GrammarRule("LISTA_DE_PARAMETROS_PROCESO_FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("token_coma");
        rightpart.add("EXPRESION");
        rightpart.add("LISTA_DE_PARAMETROS_PROCESO_FUNCION_VARIANTE_1");
        this.grammar.add(new GrammarRule("LISTA_DE_PARAMETROS_PROCESO_FUNCION_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("epsilon");
        this.grammar.add(new GrammarRule("LISTA_DE_PARAMETROS_PROCESO_FUNCION_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("numero");
        this.grammar.add(new GrammarRule("TIPO",rightpart));
        rightpart.clear();
        rightpart.add("numerico");
        this.grammar.add(new GrammarRule("TIPO",rightpart));
        rightpart.clear();
        rightpart.add("entero");
        this.grammar.add(new GrammarRule("TIPO",rightpart));
        rightpart.clear();
        rightpart.add("real");
        this.grammar.add(new GrammarRule("TIPO",rightpart));
        rightpart.clear();
        rightpart.add("caracter");
        this.grammar.add(new GrammarRule("TIPO",rightpart));
        rightpart.clear();
        rightpart.add("texto");
        this.grammar.add(new GrammarRule("TIPO",rightpart));
        rightpart.clear();
        rightpart.add("cadena");
        this.grammar.add(new GrammarRule("TIPO",rightpart));
        rightpart.clear();
        rightpart.add("logico");
        this.grammar.add(new GrammarRule("TIPO",rightpart));
        rightpart.clear();
        rightpart.add("token_mas");
        this.grammar.add(new GrammarRule("OPERADOR",rightpart));
        rightpart.clear();
        rightpart.add("token_menos");
        this.grammar.add(new GrammarRule("OPERADOR",rightpart));
        rightpart.clear();
        rightpart.add("token_div");
        this.grammar.add(new GrammarRule("OPERADOR",rightpart));
        rightpart.clear();
        rightpart.add("token_mul");
        this.grammar.add(new GrammarRule("OPERADOR",rightpart));
        rightpart.clear();
        rightpart.add("token_mod");
        this.grammar.add(new GrammarRule("OPERADOR",rightpart));
        rightpart.clear();
        rightpart.add("token_pot");
        this.grammar.add(new GrammarRule("OPERADOR",rightpart));
        rightpart.clear();
        rightpart.add("token_igual");
        this.grammar.add(new GrammarRule("OPERADOR",rightpart));
        rightpart.clear();
        rightpart.add("token_dif");
        this.grammar.add(new GrammarRule("OPERADOR",rightpart));
        rightpart.clear();
        rightpart.add("token_menor");
        this.grammar.add(new GrammarRule("OPERADOR",rightpart));
        rightpart.clear();
        rightpart.add("token_mayor");
        this.grammar.add(new GrammarRule("OPERADOR",rightpart));
        rightpart.clear();
        rightpart.add("token_menor_igual");
        this.grammar.add(new GrammarRule("OPERADOR",rightpart));
        rightpart.clear();
        rightpart.add("token_mayor_igual");
        this.grammar.add(new GrammarRule("OPERADOR",rightpart));
        rightpart.clear();
        rightpart.add("token_y");
        this.grammar.add(new GrammarRule("OPERADOR",rightpart));
        rightpart.clear();
        rightpart.add("token_o");
        this.grammar.add(new GrammarRule("OPERADOR",rightpart));
        rightpart.clear();
        rightpart.add("token_asig");
        rightpart.add("id");
        rightpart.add("ARGUMENTOS_PROCESO_FUNCION");
        this.grammar.add(new GrammarRule("DESCRIPCION_FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("ARGUMENTOS_PROCESO_FUNCION");
        this.grammar.add(new GrammarRule("DESCRIPCION_FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("epsilon");
        this.grammar.add(new GrammarRule("DESCRIPCION_FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("token_par_izq");
        rightpart.add("LISTA_DE_ARGUMENTOS_PROCESO_FUNCION");
        rightpart.add("token_par_der");
        this.grammar.add(new GrammarRule("ARGUMENTOS_PROCESO_FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("epsilon");
        this.grammar.add(new GrammarRule("ARGUMENTOS_PROCESO_FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("id");
        rightpart.add("LISTA_DE_ARGUMENTOS_PROCESO_FUNCION_VARIANTE_1");
        this.grammar.add(new GrammarRule("LISTA_DE_ARGUMENTOS_PROCESO_FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("epsilon");
        this.grammar.add(new GrammarRule("LISTA_DE_ARGUMENTOS_PROCESO_FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("token_coma");
        rightpart.add("id");
        rightpart.add("LISTA_DE_ARGUMENTOS_PROCESO_FUNCION_VARIANTE_1");
        this.grammar.add(new GrammarRule("LISTA_DE_ARGUMENTOS_PROCESO_FUNCION_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("epsilon");
        this.grammar.add(new GrammarRule("LISTA_DE_ARGUMENTOS_PROCESO_FUNCION_VARIANTE_1",rightpart));
        rightpart.clear();
        rightpart.add("finfuncion");
        this.grammar.add(new GrammarRule("FIN_PROCESO_FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("finsubproceso");
        this.grammar.add(new GrammarRule("FIN_PROCESO_FUNCION",rightpart));
        rightpart.clear();
        rightpart.add("INICIO_PROCESO");
        rightpart.add("id");
        rightpart.add("BLOQUE_PROCESO");
        this.grammar.add(new GrammarRule("PROCESO",rightpart));
        rightpart.clear();
        rightpart.add("proceso");
        this.grammar.add(new GrammarRule("INICIO_PROCESO",rightpart));
        rightpart.clear();
        rightpart.add("algoritmo");
        this.grammar.add(new GrammarRule("INICIO_PROCESO",rightpart));
        rightpart.clear();
        rightpart.add("BLOQUE");
        rightpart.add("FIN_PROCESO");
        this.grammar.add(new GrammarRule("BLOQUE_PROCESO",rightpart));
        rightpart.clear();
        rightpart.add("finproceso");
        this.grammar.add(new GrammarRule("FIN_PROCESO",rightpart));
        rightpart.clear();
        rightpart.add("finalgoritmo");
        this.grammar.add(new GrammarRule("FIN_PROCESO",rightpart));
    }

    void setPredictions () {
        for (GrammarRule grammar : this.grammar){
            this.reviewedRules.clear();
            grammar.predictions = this.predict(grammar.rule, grammar.rightpart);
            if (grammar.rule.equals("FUNCION") && grammar.rightpart.get(0).equals("epsilon")) {
                grammar.predictions.add("eof");
            }
        }
    }

    ArrayList<String> firstOnes (ArrayList<String> chain) {
        ArrayList<String> first = new ArrayList<String>();
        if ( chain.get(0).equals("epsilon")) {
            first.add("epsilon");
        } else {
            if (this.isLower(chain.get(0))) {
                first.add(chain.get(0));
            } else {
                ArrayList<String> firstFirstElement = this.firstOnesElement(chain.get(0));
                first.addAll(firstFirstElement);
                boolean containsEpsilon = firstFirstElement.contains("epsilon");
                while(first.remove("epsilon"));
                if(containsEpsilon){
                    if(chain.size() == 1){
                        first.add("epsilon");
                    }else{
                        ArrayList<String> secondToN = new ArrayList<>();
                        for (int i = 1; i<chain.size(); i++){
                            secondToN.add(chain.get(i));
                        }
                        first.addAll(this.firstOnes(secondToN));
                    }
                }
            }
        }
        return first;
    }

    ArrayList<String> firstOnesElement (String chain) {
        ArrayList<String> first = new ArrayList<String>();
        if (this.isUpper(chain)) {
            for (GrammarRule grammar: this.grammar){
                if(grammar.rule.equals(chain)){
                    first.addAll(this.firstOnes(grammar.rightpart));
                }
            }
        } else {
            first.add(chain);
        }
        Set<String> hashSet = new HashSet<String>(first);
        first.clear();
        first.addAll(hashSet);
        return first;
    }

    ArrayList<String> nextOnes (String noter) {
        ArrayList<String> next = new ArrayList<String>();
        for (GrammarRule grammar : this.grammar){
            if (grammar.rightpart.contains(noter)) {
                // cuatro A cinco B : calcular primeros de cinco B y restarle epsilon
                String noterNext;
                if ( grammar.rightpart.indexOf(noter) < grammar.rightpart.size()-1) {
                    noterNext = grammar.rightpart.get(grammar.rightpart.indexOf(noter)+1);
                } else {
                    noterNext = "epsilon";
                }
                ArrayList<String> noterNextFirstOnes = this.firstOnesElement(noterNext);
                boolean containsEpsilon = noterNextFirstOnes.contains("epsilon");
                next.addAll(noterNextFirstOnes);
                while(next.remove("epsilon"));
                // C -> cuatro A B cinco : calcular primero de b cinco - epsilon y añadirle los sigyuientes de C
                // B -> E
                if( (containsEpsilon || noterNext.equals("epsilon")) && !noter.equals(grammar.rule)) {
                    if (iscycle(grammar)) {
                        return new ArrayList<String>();
                    } else {
                        this.reviewedRules.add(grammar.rule+grammar.rightpart);
                        next.addAll(this.nextOnes(grammar.rule));
                    }
                }
            }
        }
        return next;
    }

    boolean iscycle(GrammarRule g){
        return this.reviewedRules.contains(g.rule+g.rightpart);
    }

    ArrayList<String> predict (String noter, ArrayList<String> chain) {
        ArrayList<String> predictions = new ArrayList<String>();
        if(this.firstOnes(chain).contains("epsilon")){
            predictions.addAll(this.firstOnes(chain));
            while(predictions.remove("epsilon"));
            predictions.addAll(this.nextOnes(noter));
        } else {
            predictions.addAll(this.firstOnes(chain));
        }
        return predictions;
    }

    boolean recursiveProcessTokens (String currentGrammarRule) {
        ArrayList<GrammarRule> currentGrammarRules = new ArrayList<GrammarRule>();
        for (GrammarRule grammarRule : this.grammar){
            if(grammarRule.rule.equals(currentGrammarRule)){
                currentGrammarRules.add(grammarRule);
            }
        }
        this.goToGrammarRule= true;
        for (GrammarRule grammarRule: currentGrammarRules) {
            this.currentGrammarRule = grammarRule;
            if(this.currentGrammarRule.predictions.contains(this.currentToken.type) && this.goToGrammarRule) {
                this.goToGrammarRule = false;
                for (String grammarRuleRightPart : this.currentGrammarRule.rightpart){
                    if(this.isLower(grammarRuleRightPart)) {
                        if(!this.match(grammarRuleRightPart)) {
                            return false;
                        };
                    } else {
                        if(!recursiveProcessTokens(grammarRuleRightPart)) {
                            return false;
                        };
                    }
                }
            }
        }
        if (goToGrammarRule) {
            Error error = new Error(this.currentToken.row, this.currentToken.col);
            //System.out.println(this.currentGrammarRule.rule + this.currentGrammarRule.rightpart + this.currentGrammarRule.predictions);
            System.out.println(error.returnSintacticErrorMessage(this.currentToken.lexeme,this.currentGrammarRule.predictions));
            return false;
        } else {
            return true;
        }
    }

    boolean match (String expectedToken) {
        if (this.currentToken.type.equals(expectedToken)) {
            if(expectedToken.equals("eof")) {
                return true;
            }
            this.currentToken = this.tokens.get(this.tokens.indexOf(this.currentToken) + 1);
            return true;
        } else if (expectedToken.equals("epsilon")) {
            return true;
        } else {
            Error error = new Error(this.currentToken.row, this.currentToken.col);
            //System.out.println(this.currentGrammarRule.rule + this.currentGrammarRule.rightpart + this.currentGrammarRule.predictions);
            ArrayList<String> expected = new ArrayList<String>();
            expected.add(expectedToken);
            System.out.println(error.returnSintacticErrorMessage(this.currentToken.lexeme,expected));
            return false;
        }
    }

    boolean isLower (String s) {
        return s.equals(s.toLowerCase());
    }

    boolean isUpper (String s) {
        return s.equals(s.toUpperCase());
    }
}
