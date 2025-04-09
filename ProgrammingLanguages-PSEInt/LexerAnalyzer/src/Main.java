import java.io.IOException;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) throws IOException {
        Lexicon lexicon = new Lexicon();
        ArrayList<Token> tokens = lexicon.getTokens();
        for (Token token : tokens){
            if(token.getLexeme()!=""){
                System.out.println("<"+token.getType()+","+token.getLexeme()+","+token.getRow()+","+token.getCol()+">");
            }else{
                System.out.println("<"+token.getType()+","+token.getRow()+","+token.getCol()+">");
            }
        }
        if(lexicon.hasError()){
            System.out.println(lexicon.getError());
        }
    }
}
