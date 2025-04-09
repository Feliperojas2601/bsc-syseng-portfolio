import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;

public class Main {
    public static void main(String[] args) throws Exception {
        //try{

            GrammarLexer lexer;
            if (args.length>0) {
                lexer = new GrammarLexer(CharStreams.fromFileName(args[0]));
            }else {
                lexer = new GrammarLexer(CharStreams.fromStream(System.in));
            }

            CommonTokenStream tokens = new CommonTokenStream(lexer);
            GrammarParser parser = new GrammarParser(tokens);
            ParseTree tree = parser.programa();
            System.out.println(tree.toStringTree(parser));

            MyVisitor<Object> loader = new MyVisitor<Object>();
            loader.visit(tree);
/*
    } catch (Exception e){
            System.err.println("Error (Test): " + e);
        }

 */
    }
}
