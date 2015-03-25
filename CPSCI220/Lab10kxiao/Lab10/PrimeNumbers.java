import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

public class PrimeNumbers {
    /** List of numbers **/
    public static List<Integer> listNo(int max) {
	List<Integer> result = new ArrayList<Integer>();
	for (int i = 2; i <= max; i++){
	    result.add(i);
	}
	return result;
    }

    public static void selectPrime(List<Integer> list){
	int max = list.get(list.size()-1);
    	for (int i = 2; i <= max; i++){
	    Iterator<Integer> iterate = list.iterator();
	    while(iterate.hasNext()){
		int element = iterate.next();
		if(element != i && element % i == 0){
		    iterate.remove();
		}
	    }
	}
    }
	

    /** A test method */
    public static void main(String[] args) {
	int max = Integer.parseInt(args[0]);
	List<Integer> list = listNo(max);
	selectPrime(list);
	for(int i : list){
	    System.out.println(i);
	}
    }
}
