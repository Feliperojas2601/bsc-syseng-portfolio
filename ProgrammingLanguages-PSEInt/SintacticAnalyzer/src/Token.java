public class Token {

    public String lexeme, type;
    public int col, row;

    public Token(String lexeme, String type, int row, int col) {
        this.lexeme = lexeme;
        this.type = type;
        this.col = col;
        this.row = row;
    }

    public Token(int row, int col){
        this.row= row;
        this.col = col;
    }

    public String getLexeme() {
        return lexeme;
    }

    public String getType() {
        return type;
    }

    public int getCol() {
        return col;
    }

    public int getRow() {
        return row;
    }

    public void setLexeme(String lexeme) {
        this.lexeme = lexeme;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void setCol(int col) {
        this.col = col;
    }

    public void setRow(int row) {
        this.row = row;
    }
}
