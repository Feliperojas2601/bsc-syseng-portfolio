import java.util.ArrayList;

public class GrammarRule {
    public String rule;
    public ArrayList<String> rightpart;
    public ArrayList<String> predictions = new ArrayList<String>();

    GrammarRule(String rule, ArrayList<String> rightpart){
        this.rule = rule;
        this.rightpart = new ArrayList<String>();
        this.rightpart.addAll(rightpart);
    }
}
