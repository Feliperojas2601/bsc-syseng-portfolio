import java.io.IOException;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) throws IOException {
        Lexicon lexicon = new Lexicon();
        ArrayList<Token> tokens = lexicon.getTokens();
        Sintactic sintactic = new Sintactic(tokens);
    }
}
