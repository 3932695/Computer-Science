// CPSCI 220 - Lab 8 - Kevin Xiao - Due Tuesday April 29th

import java.util.concurrent.*;

public class Lab10 {
    public static void main(String[] args) {
	long max = Long.parseLong(args[0]);

	MyLinkedList<Long> list1 = PrimeNumbers.listNo(max);    
	long startTime1 = System.currentTimeMillis();
	prime(list1); // Invoke parallel prime selection
	long endTime1 = System.currentTimeMillis();

	MyLinkedList<Long> list2 = PrimeNumbers.listNo(max);
	long startTime2 = System.currentTimeMillis();
	PrimeNumbers.prime(list2); // Standard prime selection
	long endTime2 = System.currentTimeMillis();

	System.out.println("List of prime numbers up to " + max + "...");
	System.out.println("Parallel results: ");
	Lab8.displayList(list1);
	System.out.println("Sequential results: ");
	Lab8.displayList(list2);

	System.out.println("\nParallel time with "
			   + Runtime.getRuntime().availableProcessors() + 
			   " processors is " + (endTime1 - startTime1) + 
			   " milliseconds");

	System.out.println("\nSequential time is " + 
			   (endTime2 - startTime2) + " milliseconds");

    }

    public static void prime(MyLinkedList<Long> list) {
	RecursiveAction mainTask = new PrimeTask(list, list.size() / 2);
	ForkJoinPool pool = new ForkJoinPool();
	pool.invoke(mainTask);
    }

    private static class PrimeTask extends RecursiveAction {
	private long THRESHOLD;
	private MyLinkedList<Long> list;

	// Awkward programming note: 
	// Going beyond the first level of recursion kept throwing errors.
	// I couldn't locate the source of error. So instead, I guarantee
	// ...just one level of recursion by having the THRESHOLD vary with
	///...the range of our search for primes. 
	PrimeTask(MyLinkedList<Long> list, long THRESHOLD) {
	    this.list = list;
	    this.THRESHOLD = THRESHOLD;
	}
	
	@Override
	protected void compute() {
	    long size = this.list.size();
	    if (size < THRESHOLD)
		PrimeNumbers.prime(this.list);
	    else {
		long mid = this.list.get(size / 2);

		// Retrieve second half of LinkedList.
		MyLinkedList<Long> secondHalf = new MyLinkedList<Long>();
		secondHalf.head = this.list.getNode(mid);
		secondHalf.tail = this.list.getNode(mid).getNext();
		secondHalf.size = size - mid;
		
		// Retrieve first half of LinkedList.
		MyLinkedList<Long> firstHalf = new MyLinkedList<Long>();
		firstHalf.head = this.list.head;
		firstHalf.tail = this.list.tail;
		firstHalf.size = mid;
		firstHalf.getNode(mid - 1).setNext(null);

		// Recursively apply prime selection to both halves.
		invokeAll(new PrimeTask(firstHalf, THRESHOLD), 
			  new PrimeTask(secondHalf, THRESHOLD));
	    
		// Merge the LinkedLists.
		firstHalf.last().setNext(secondHalf.head);
		this.list.head = firstHalf.head;
		this.list.tail = firstHalf.tail;
		this.list.size = firstHalf.size + secondHalf.size;
	    }
	}
    }

}
