import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Lexicon {

    public HashMap<String, String> operatorToken = new HashMap<>();
    public HashMap<String, String> reservedToken = new HashMap<>();
    public ArrayList<String> reservedWords = new ArrayList<>();
    public ArrayList<String> symbols = new ArrayList<String>();
    public ArrayList<Token> tokens = new ArrayList<>();
    public String input = "";
    public int row = 1;
    public int col = 1;
    public int colIndex = this.col-1;
    public Character finalInput = '\0';
    public Boolean finish = false;
    public String error = "";
    public Boolean is_int_point = false;

    public Lexicon() throws IOException {
        this.fillOperatorsTokens();
        this.fillreservedWords();
        this.fillSymbols();
        this.fillReservedWordsAsTokens();
        this.readInput();
        this.processInput();
    }

    public void fillOperatorsTokens(){
        this.operatorToken.put("~","token_neg");
        this.operatorToken.put("=","token_igual");
        this.operatorToken.put("<-","token_asig");
        this.operatorToken.put("<>","token_dif");
        this.operatorToken.put("<","token_menor");
        this.operatorToken.put(">","token_mayor");
        this.operatorToken.put("<=","token_menor_igual");
        this.operatorToken.put(">=","token_mayor_igual");
        this.operatorToken.put("+","token_mas");
        this.operatorToken.put("-","token_menos");
        this.operatorToken.put("/","token_div");
        this.operatorToken.put("*","token_mul");
        this.operatorToken.put("%","token_mod");
        this.operatorToken.put(";","token_pyc");
        this.operatorToken.put(":","token_dosp");
        this.operatorToken.put("(","token_par_izq");
        this.operatorToken.put(")","token_par_der");
        this.operatorToken.put("[","token_cor_izq");
        this.operatorToken.put("]","token_cor_der");
        this.operatorToken.put("|","token_o");
        this.operatorToken.put("&","token_y");
        this.operatorToken.put(",","token_coma");
        this.operatorToken.put("^","token_pot");
        this.operatorToken.put("", "id");
    }

    public void fillReservedWordsAsTokens(){
        this.reservedToken.put("o","token_o");
        this.reservedToken.put("y", "token_y");
        this.reservedToken.put("no", "token_neg");
        this.reservedToken.put("mod", "token_mod");
    }

    public void fillSymbols(){
        this.symbols.add("~");
        this.symbols.add("=");
        this.symbols.add("<");
        this.symbols.add("-");
        this.symbols.add(">");
        this.symbols.add("+");
        this.symbols.add("-");
        this.symbols.add("/");
        this.symbols.add("*");
        this.symbols.add("%");
        this.symbols.add(";");
        this.symbols.add(":");
        this.symbols.add("(");
        this.symbols.add(")");
        this.symbols.add("[");
        this.symbols.add("]");
        this.symbols.add("|");
        this.symbols.add("&");
        this.symbols.add(",");
        this.symbols.add("^");
        this.symbols.add("\"");
        this.symbols.add("\'");
    }

    public void fillreservedWords(){
        this.reservedWords.add("caracter");
        this.reservedWords.add("real");
        this.reservedWords.add("entero");
        this.reservedWords.add("numerico");
        this.reservedWords.add("numero");
        this.reservedWords.add("logico");
        this.reservedWords.add("texto");
        this.reservedWords.add("cadena");
        this.reservedWords.add("verdadero");
        this.reservedWords.add("falso");
        this.reservedWords.add("y");
        this.reservedWords.add("o");
        this.reservedWords.add("no");
        this.reservedWords.add("mod");
        this.reservedWords.add("para");
        this.reservedWords.add("hasta");
        this.reservedWords.add("con");
        this.reservedWords.add("paso");
        this.reservedWords.add("definir");
        this.reservedWords.add("hacer");
        this.reservedWords.add("como");
        this.reservedWords.add("escribir");
        this.reservedWords.add("leer");
        this.reservedWords.add("entonces");
        this.reservedWords.add("dimension");
        this.reservedWords.add("repetir");
        this.reservedWords.add("mientras");
        this.reservedWords.add("algoritmo");
        this.reservedWords.add("proceso");
        this.reservedWords.add("si");
        this.reservedWords.add("sino");
        this.reservedWords.add("segun");
        this.reservedWords.add("de");
        this.reservedWords.add("otro");
        this.reservedWords.add("modo");
        this.reservedWords.add("subproceso");
        this.reservedWords.add("subalgoritmo");
        this.reservedWords.add("funcion");
        this.reservedWords.add("finproceso");
        this.reservedWords.add("finalgoritmo");
        this.reservedWords.add("finmientras");
        this.reservedWords.add("finsi");
        this.reservedWords.add("finsegun");
        this.reservedWords.add("finpara");
        this.reservedWords.add("finsubproceso");
        this.reservedWords.add("finsubalgoritmo");
        this.reservedWords.add("finfuncion");
        this.reservedWords.add("hasta");
        this.reservedWords.add("que");
        this.reservedWords.add("limpiar");
        this.reservedWords.add("borrar");
        this.reservedWords.add("pantalla");
        this.reservedWords.add("esperar");
        this.reservedWords.add("tecla");
        this.reservedWords.add("segundos");
        this.reservedWords.add("milisegundos");
        this.reservedWords.add("rc");
        this.reservedWords.add("raiz");
        this.reservedWords.add("abs");
        this.reservedWords.add("ln");
        this.reservedWords.add("exp");
        this.reservedWords.add("sen");
        this.reservedWords.add("cos");
        this.reservedWords.add("tan");
        this.reservedWords.add("asen");
        this.reservedWords.add("acos");
        this.reservedWords.add("atan");
        this.reservedWords.add("redon");
        this.reservedWords.add("aleatorio");
        this.reservedWords.add("longitud");
        this.reservedWords.add("mayusculas");
        this.reservedWords.add("minusculas");
        this.reservedWords.add("subcadena");
        this.reservedWords.add("concatenar");
        this.reservedWords.add("convertiranumero");
        this.reservedWords.add("convertiratexto");
    }

    public void readInput() throws IOException {
        BufferedReader scanner = new BufferedReader(new InputStreamReader(System.in));
        String readLine = "";
        while((readLine = scanner.readLine())!= null) {
            this.input += readLine;
            this.input += "\n";
        }
        scanner.close();
        this.input = this.input + this.finalInput;
    }

    public void processInput() {
        this.lineIsCommentOrBlank();
        while ((this.input.charAt(this.colIndex) != this.finalInput) && (this.finish == false)) {
            Token token = new Token(this.row, this.col);
            StringBuilder tokenLexem = new StringBuilder();
            char symbol = this.input.charAt(this.colIndex);
            if (this.isChar(symbol)) {
                symbol = this.input.charAt(this.colIndex);
                while (isChar(symbol) || symbol == '_' || isNumber(symbol)) {
                    tokenLexem.append(symbol);
                    this.col++;
                    this.colIndex++;
                    symbol = this.input.charAt(colIndex);
                }
                token.setLexeme(tokenLexem.toString().toLowerCase());
                if (this.operatorToken.containsKey(token.getLexeme())) {
                    token.setType(this.operatorToken.get(token.getLexeme().toLowerCase()));
                    token.setLexeme("");
                } else if (this.reservedWords.contains(token.getLexeme().toLowerCase())){
                    if(this.isReservedAsToken(token.getLexeme())){
                        token.setType(this.reservedToken.get(token.getLexeme()));
                        token.setLexeme("");
                    }else{
                        token.setType(token.getLexeme().toLowerCase());
                        token.setLexeme("");
                    }
                } else {
                    token.setType("id");
                }
            } else if (this.isNumber(symbol)) {
                if (!this.isNumber(this.input.charAt(this.colIndex))) {
                    token.setType(this.operatorToken.get(token.getLexeme()));
                    token.setLexeme("");
                } else {
                    symbol = this.input.charAt(this.colIndex);
                    char symbolAux = this.input.charAt(this.colIndex);
                    boolean is_real = false;
                    is_int_point = false;
                    int aux = colIndex;
                    while (this.isNumber(symbolAux)){
                        if(isChar(this.input.charAt(aux+1)) && this.input.charAt(aux+1) != '.'){
                            Error error = new Error(this.row, this.col);
                            this.error = error.returnErrorMessage();
                            finish = true;
                            break;
                        }
                        aux ++;
                        symbolAux = this.input.charAt(aux);
                    }
                    while ((!is_real && symbol == '.') || (this.isNumber(symbol))) {
                        this.col++;
                        this.colIndex++;
                        if (symbol == '.' && isNumber(this.input.charAt(this.colIndex))) {
                            is_real = true;
                        } else if (symbol == '.' && this.input.charAt(colIndex) == ' '){
                            is_int_point = true;
                        }
                        if(!is_int_point){
                            tokenLexem.append(symbol);
                        }
                        symbol = this.input.charAt(this.colIndex);
                    }
                    token.setLexeme(tokenLexem.toString());
                    if (is_real) {
                        token.setType("token_real");
                    } else if (symbol == '.' || is_real ) {
                        Error error = new Error(this.row, this.col);
                        this.error = error.returnErrorMessage();
                        finish = true;
                    } else {
                        token.setType("token_entero");
                    }
                }
            } else if (this.isSymbol(symbol)) {
                if (symbol == '\"' || symbol == '\'') {
                    int aux = colIndex + 1;
                    while (this.input.charAt(aux) != '\"' && this.input.charAt(aux) != '\'' && this.input.charAt(aux) != this.finalInput) {
                        aux++;
                    }
                    if (this.input.charAt(aux) == '\"' || this.input.charAt(aux) == '\'') {
                        this.col++;
                        this.colIndex++;
                        StringBuilder chain = new StringBuilder();
                        while (this.input.charAt(this.colIndex) != '\"' && this.input.charAt(this.colIndex) != '\'') {
                            chain.append(this.input.charAt(colIndex));
                            this.col++;
                            this.colIndex++;
                        }
                        token.setLexeme(chain.toString());
                        token.setType("token_cadena");
                        this.col++;
                        this.colIndex++;
                    } else {
                        Error error = new Error(row, col);
                        this.error = error.returnErrorMessage();
                        finish = true;
                    }
                } else {
                    String simpleSymbol = "";
                    String doubleSymbol = "";
                    simpleSymbol = Character.toString(symbol);
                    doubleSymbol = Character.toString(symbol) + Character.toString(this.input.charAt(this.colIndex + 1));
                    if (this.operatorToken.containsKey(doubleSymbol)) {
                        token.setLexeme(doubleSymbol);
                        token.setType(this.operatorToken.get(token.getLexeme()));
                        token.setLexeme("");
                        this.colIndex = this.colIndex + 2;
                        this.col = this.col + 2;
                    } else {
                        token.setLexeme(simpleSymbol);
                        token.setType(this.operatorToken.get(token.getLexeme()));
                        token.setLexeme("");
                        this.colIndex++;
                        this.col++;
                    }
                }
            }else{
                Error error = new Error(row, col);
                this.error = error.returnErrorMessage();
                finish = true;
            }
            if(!finish){
                this.tokens.add(token);
            }
            this.lineIsCommentOrBlank();
        }
    }

    public void lineIsCommentOrBlank(){
        boolean useless = false;
        do{
            useless = false;
            if(this.input.charAt(this.colIndex)=='/' && this.input.charAt(this.colIndex+1)=='/' ){
                while(this.input.charAt(this.colIndex)!= '\n'){
                    this.colIndex++;
                    this.col++;
                }
                useless = true;
            }
            while(isUselessSpace(this.input.charAt(this.colIndex))){
                if(this.input.charAt(this.colIndex) == '\n'){
                    this.col = 1;
                    this.row++;
                }else{
                    this.col++;
                }
                this.colIndex++;
                useless = true;
            }
        }while(useless);
        useless = false;
    }

    public boolean isUselessSpace( char symbol ){
        if(symbol == '\r' || symbol == '\n' || symbol == ' ' || symbol == '\t'){
            if(this.is_int_point && symbol == ' '){
                Error error = new Error(row, col-1);
                this.error = error.returnErrorMessage();
                finish = true;
            }
            return true;
        }else{
            return false;
        }
    }

    public boolean isChar( char symbol ){
        if((symbol >= 'a' && symbol <='z')  || (symbol >= 'A' && symbol <='Z')){
            return true;
        }else{
            return false;
        }
    }

    public boolean isNumber( char symbol ){
        if(symbol >= '0' && symbol <='9'){
            return true;
        }else{
            return false;
        }
    }

    public boolean isSymbol( char symbol ){
        if (this.symbols.contains(Character.toString(symbol))){
            return true;
        } else {
            return false;
        }
    }

    public boolean isReservedAsToken(String reserved){
        if(this.reservedToken.containsKey(reserved)){
            return true;
        }else{
            return false;
        }
    }

    public boolean hasError(){
        if (this.error.equals("")) {
            return false;
        } else {
            return true;
        }
    }

    public ArrayList<Token> getTokens() {
        return tokens;
    }

    public String getError() {
        return error;
    }
}
