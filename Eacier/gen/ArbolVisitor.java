// Generated from C:/Users/PERSONAL/Documents/Proyectos/Independientes/Lenguajes de Programaci�n/Eacier/grammar\Arbol.g4 by ANTLR 4.9.2
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link ArbolParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface ArbolVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link ArbolParser#arbol}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArbol(ArbolParser.ArbolContext ctx);
	/**
	 * Visit a parse tree produced by {@link ArbolParser#raiz}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRaiz(ArbolParser.RaizContext ctx);
}