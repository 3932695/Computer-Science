// Generates a LinkedList of prime numbers. 
// Makes a list of numbers up to a specified maximum, and then removes numbers
// ...divisible by 2, 3, 4, 5, and so on until half of the maximum is reached.
// Ignores divided = divisor case (2 is divisible by 2 will not remove 2).
// Not particularly efficient (although effiency isn't really the point).


public class PrimeNumbers {
    /** List of numbers **/
    public static MyLinkedList<Long> listNo(long max) {
	MyLinkedList<Long> result = new MyLinkedList<Long>();
	for (long i = 2; i <= max; i++){
	    result.addLast(i);
	}
	return result;
    }

    public static void prime(MyLinkedList<Long> list){
	long max = list.getLast();
    	for (long i = 2; i <= max/2; i++){
	    long current = 0;
	    while(current < list.size()){
		long element = list.get(current);
		if(element != i && element % i == 0){
		    list.remove(current);
		}
		current = current + 1;	
	    }
	}
    }
	

    /** A test method */
    public static void main(String[] args) {
	long max = Long.parseLong(args[0]);
	MyLinkedList<Long> list = listNo(max);
	prime(list);
	
	// Print list
	Lab8.displayList(list);
	
    }
}
