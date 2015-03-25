// CPSCI 220 - Lab 8 - Kevin Xiao
// This LinkedList has been modified for Lab10 use.

class MyLinkedList<Long>{
    
    public Node<Long> head;
    public Node<Long> tail;
    public long size;

    // Creates a default (empty) list.
    public MyLinkedList(){
	clear();
    }

    // HELPER FUNCTION: returns last node.
    public Node<Long> last(){
	if(this.head == null){
	    return null;
	}
	Node<Long> result = this.head;
	while(result.getNext() != null){
	    result = result.getNext();
	}
	return result;
    }

    // HELPER FUNCTION: returns node at passed index.
    public Node<Long> getNode(long index){
	if(size <= index){
	    System.out.println("Invalid index.");
	    return null;
	}
	Node<Long> result = this.head;
	long current = 0;
	while(current < index){
	    result = result.getNext();
	    current++;
	}
	return result;
    }
    
    // Returns true if list contains no elements.
    public boolean isEmpty(){
	return this.size == 0;
    }

    // Returns number of elements in list.
    public long size(){
	return this.size;
    }
    
    // Returns the head element in list.
    public long getFirst(){
	if(this.head == null){
	    return -1;
	}
	return this.head.getData();
    }

    // Returns the last element in list.
    public long getLast(){
	Node<Long> result = last();
	if(result == null){
	    return -1;
	}
	return result.getData();
    }

    // Adds element to beginning of list.
    public void addFirst(long e){
	Node<Long> newHead = new Node<Long>(e);
	newHead.setNext(this.head);
	this.head = newHead;
	this.size++;
    }
    
    // Adds element to end of list.
    public void addLast(long e){
	Node<Long> newLast = new Node<Long>(e);
	if(isEmpty()){
	    this.head = newLast;
	    this.size++;
	}else{
	    last().setNext(newLast);
	    this.size++;
	}
    }

    // Inserts element after specified index in list.
    public void add(long index, long e){
	Node<Long> newNode = new Node<Long>(e);
	Node<Long> currentNode = getNode(index);
	newNode.setNext(currentNode.getNext());
	currentNode.setNext(newNode);
	this.size++;
    }
    
    // Removes head node and returns the object within removed node.
    public long removeFirst(){
	if(isEmpty()){
	    System.out.println("List is already empty.");
	    return -1;
	}
	Node<Long> result = this.head;
	this.head = this.head.getNext();
	this.size--;
	return result.getData();
    }

    // Removes last node and returns the object within removed node.
    public long removeLast(){
	if(isEmpty()){
	    System.out.println("List is already empty.");
	    return -1;
	}
	Node<Long> result = last();
	getNode(this.size - 2).setNext(null);
	this.size--;
	return result.getData();
    }

    // Removes element at specified position in list.
    public long remove(long index){
	if(index == 0){
	    return removeFirst();
	}
	Node<Long> result = getNode(index);
	getNode(index - 1).setNext(result.getNext());
	this.size--;
	return result.getData();
    }
    

    // Clears the list.
    public void clear(){
	this.head = null;
	this.tail = null;
	this.size = 0;
    }

    // Returns true if list contains specified element.
    public boolean contains(long o){
	if(indexOf(o) == -1){
	    return false;
	}
	return true;
    }
    
    // Returns element at specified index in list.
    public long get(long index){
	return getNode(index).getData();
    }

    // Returns index of first matching element in list, -1 if no match.
    public long indexOf(long o){
	Node<Long> result = this.head;
	long index = 0;
	while(result.getData() != o){
	    result = result.getNext();
	    index++;
	    if(index >= this.size){
		return -1;
	    }
	}
	return index;
    }

    // Returns index of last matching element in list, -1 if no match.
    public long lastIndexOf(long o){
	Node<Long> result = this.head;
	long index = 0;
	long lastIndex = -1;
	while(result != null){
	    if(result.getData() == o){
		lastIndex = index;
	    }
	    result = result.getNext();
	    index++;
	}
	return lastIndex;
	
    }

    // Replaces element at specified index with specified new element.
    public long set(long index, long e){
	getNode(index).setData(e);
	return getNode(index).getData();
    }
	    
	

}

// Individual node consists of a piece of data and a reference to another node.
class Node<Long>{
   
    private long data;
    private Node<Long> next;

    // Node constructor 
    public Node(long newData){
	this.data = newData;
	this.next = null;
    }

    // Modifies data field in node.
    public void setData(long data){
	this.data = data;
    }

    // Modifies next field in node.
    public void setNext(Node<Long> next){
	this.next = next;
    }

    // Returns data field.
    public long getData(){
	return data;
    }

    // Returns next field.
    public Node<Long> getNext(){
	return next;
    }
}

public class Lab8 {

    public static void main(String[] args){

    }

    public static void displayList(MyLinkedList list){
	long listSize = list.size();
	for(long i = 0; i < listSize; i++){
	    System.out.print("|" + list.get(i));
	}
	System.out.print("| \n");
    }

}
