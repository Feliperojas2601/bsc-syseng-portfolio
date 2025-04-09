import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;

public class Error {

    public int row;
    public int col;
    public ArrayList<String> predictions;
    public HashMap<String, String> operatorToken = new HashMap<>();

    public Error(int row, int col){
        this.row = row;
        this.col = col;
    }


    public String returnErrorMessage(){
        return ">>> Error lexico (linea: "+this.row+", posicion: "+this.col+")\n";
    }

    public String returnSintacticErrorMessage(String token, ArrayList<String> expected){
        this.setOperators();
        if (expected.contains("id")) {
            expected.remove("id");
            expected.add("identificador");
        }
        Collections.sort(expected);
        String expectedString = "";
        for (int i = 0; i<expected.size(); i++) {
            if (this.operatorToken.containsKey(expected.get(i))) {
                expectedString = expectedString + "\""+this.operatorToken.get(expected.get(i))+"\"";
            } else {
                expectedString = expectedString + "\""+expected.get(i)+"\"";
            }
            if (i != expected.size()-1) {
                expectedString = expectedString + ", ";
            }
        }
        return "<"+this.row+":"+this.col+">"+" Error sintactico: se encontro: \""+token+"\"; se esperaba: "+expectedString+".";
    }

    public void setOperators(){
        this.operatorToken.put("token_cadena","valor_cadena");
        this.operatorToken.put("token_asig", "<-");
        this.operatorToken.put("token_coma",",");
        this.operatorToken.put("token_cor_der", "]");
        this.operatorToken.put("token_cor_izq", "[");
        this.operatorToken.put("token_dif","<>");
        this.operatorToken.put("token_div","/");
        this.operatorToken.put("token_dosp", ":");
        this.operatorToken.put("token_entero","valor_entero");
        this.operatorToken.put("token_igual", "=");
        this.operatorToken.put("token_mas", "+");
        this.operatorToken.put("token_mayor_igual", ">=");
        this.operatorToken.put("token_mayor", ">");
        this.operatorToken.put("token_menor", "<");
        this.operatorToken.put("token_menor_igual", ">");
        this.operatorToken.put("token_menos", "-");
        this.operatorToken.put("token_mod", "%");
        this.operatorToken.put("token_mul", "*");
        this.operatorToken.put("token_neg", "~");
        this.operatorToken.put("token_o", "|");
        this.operatorToken.put("token_par_der", ")");
        this.operatorToken.put("token_par_izq", "(");
        this.operatorToken.put("token_pot", "^");
        this.operatorToken.put("token_pyc", ";");
        this.operatorToken.put("token_real", "valor_real");
        this.operatorToken.put("token_y", "&");
    }
}
