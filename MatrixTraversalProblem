import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;

// Position class encapsulates the coordinate position in two-dimensional system
class Position {
	int x, y;

	public Position() {
		this.x = 0;
		this.y = 0;
	}

	public Position(int x, int y) {
		this.x = x;
		this.y = y;
	}

	// Multiply this position by constant value
	public void scale(int n) {
		this.x = n * this.x;
		this.y = n * this.y;
	}

	// Add another position to this position
	public void add(Position that) {
		this.x += that.x;
		this.y += that.y;
	}

	// Print this position
	public String toString() {
		return x + "," + y;
	}

}

// Move class encapsulates the direction to move in and the number of steps to be taken
class Move {
	char direction;
	int steps;

	public Move() {
		this.direction = ' ';
		this.steps = 0;
	}

	public Move(char direction, int steps) {
		this.direction = direction;
		this.steps = steps;
	}
}

// Matrix traversal solution class
class MatrixTraverser {

	// Direction to position increment map
	Map<Character, Position> directionToPositionIncrement;

	// List of input moves
	List<Move> moves;

	// Initial position to start from
	Position initialPosition;

	// Initialize system globals
	public void init() {
		this.directionToPositionIncrement = new HashMap<Character, Position>();
		this.directionToPositionIncrement.put('L', new Position(-1, 0));
		this.directionToPositionIncrement.put('R', new Position(1, 0));
		this.directionToPositionIncrement.put('U', new Position(0, 1));
		this.directionToPositionIncrement.put('D', new Position(0, -1));
	}

	public MatrixTraverser(List<Move> moves) {
		init();
		this.moves = moves;
		this.initialPosition = new Position();
	}

	public MatrixTraverser(List<Move> moves, Position initialPosition) {
		init();
		this.moves = moves;
		this.initialPosition = initialPosition;
	}

	// Traverse the matrix and return the final position at the end
	public Position traverse() {

		// Initialize current position
		Position currentPosition = new Position(initialPosition.x,
				initialPosition.y);

		// Iterate through input moves
		for (Move currentMove : moves) {

			// Fetch position increment for current direction
			Position positionIncrement = directionToPositionIncrement.get(currentMove.direction);

			// Scale position increment by number of steps
			positionIncrement.scale(currentMove.steps);

			// Add position increment to current position
			currentPosition.add(positionIncrement);
		}

		return currentPosition;
	}
}

// Matrix traversal driver class
public class MatrixTraversalProblem {

	// Valid directions
	public static List<Character> directions = new ArrayList<Character>();

	// Input reader
	public static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

	// Initialize system globals
	public static void init() {
		directions.add('L');
		directions.add('R');
		directions.add('U');
		directions.add('D');
	}

	// Read input string
	public static String readInput() throws Exception {
		return br.readLine();
	}

	// Parse input string and construct series of moves
	// Return null if input is in invalid format
	public static List<Move> parseInput(String input) {
		List<Move> moves = new ArrayList<Move>();
		Move currentMove;

		StringTokenizer tokenizer = new StringTokenizer(input, ",");
		String token;

		while (tokenizer.hasMoreTokens()) {
			token = tokenizer.nextToken();

			if (!isValidToken(token)) {
				return null;
			}

			token = token.trim();

			currentMove = new Move(token.charAt(0), Integer.parseInt(token.substring(1)));
			moves.add(currentMove);

		}
		return moves;
	}

	// Validate input token for correct format
	public static boolean isValidToken(String token) {
		if (token == null || token.trim().length() < 2) {
			return false;
		}

		token = token.trim();

		// Validate current direction
		char currentDirection = token.charAt(0);
		if (!directions.contains(currentDirection)) {
			return false;
		}

		// Validate current steps
		String currentSteps = token.substring(1);
		if (!isValidInteger(currentSteps)) {
			return false;
		}

		return true;

	}

	// Check for valid string
	public static boolean isValidString(String string) {
		if (string != null && string.trim().length() > 0) {
			return true;
		} else {
			return false;
		}
	}

	// Check for valid integer
	public static boolean isValidInteger(String string) {
		try {
			Integer.parseInt(string);
			return true;
		} catch (NumberFormatException ex) {
			// ex.printStackTrace();
		}
		return false;
	}

	// Main method
	public static void main(String[] args) throws Exception {

		init();
		String input = readInput();
		List<Move> moves = parseInput(input);
		if (moves == null) {
			throw new Exception("ERROR: Invalid input.");
		}

		MatrixTraverser matrixTraverser = new MatrixTraverser(moves);
		Position finalPosition = matrixTraverser.traverse();
		System.out.println(finalPosition);

	}

}
