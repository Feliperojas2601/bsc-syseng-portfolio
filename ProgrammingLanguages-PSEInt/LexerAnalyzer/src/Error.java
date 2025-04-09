public class Error {

    public int row;
    public int col;

    public Error(int row, int col){
        this.row = row;
        this.col = col;
    }

    public String returnErrorMessage(){
        return ">>> Error lexico (linea: "+this.row+", posicion: "+this.col+")\n";
    }
}
