import java.util.concurrent.*;
import java.util.List;

public class ParallelPrimeNumbers {
    public static void main(String[] args) {
	int max = Integer.parseInt(args[0]);
	List<Integer> list = PrimeNumbers.listNo(max);
    
	long startTime = System.currentTimeMillis();
	selectPrime(list); // Invoke parallel prime selection
	long endTime = System.currentTimeMillis();
	System.out.println("\nParallel time with "
			   + Runtime.getRuntime().availableProcessors() + 
			   " processors is " + (endTime - startTime) + 
			   " milliseconds");

	startTime = System.currentTimeMillis();
	PrimeNumbers.selectPrime(list); // Standard prime selection
	endTime = System.currentTimeMillis();
	System.out.println("\nSequential time is " + 
			   (endTime - startTime) + " milliseconds");
    }

    public static void selectPrime(List<Integer> list) {
	RecursiveAction mainTask = new PrimeTask(list);
	ForkJoinPool pool = new ForkJoinPool();
	pool.invoke(mainTask);
    }

    private static class PrimeTask extends RecursiveAction {
	private final int THRESHOLD = 5000;
	private List<Integer> list;


	PrimeTask(List<Integer> list) {
	    this.list = list;
	}
	
	@Override
	protected void compute() {
	    int size = list.size();
	    if (size < THRESHOLD)
		PrimeNumbers.selectPrime(list);
	    else {
		int mid = size / 2;

		// Obtain the first half
		List<Integer> firstHalf = list.subList(0, mid);
	    
		// Obtain the second half
		List<Integer> secondHalf = list.subList(mid, size);
	    
		// Recursively select primes for both halves
		invokeAll(new PrimeTask(firstHalf), 
			  new PrimeTask(secondHalf));
	    
		// No need to merge, hail Lists!
	    }
	}
    }

}
