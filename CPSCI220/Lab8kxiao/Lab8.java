// CPSCI 220 - Lab 8 - Kevin Xiao - Due April 15th 2014
// No other students were consulted for this lab.

class MyLinkedList<E>{
    
    private Node<E> head;
    private Node<E> tail;
    private int size;

    // Creates a default (empty) list.
    public MyLinkedList(){
	clear();
    }

    // HELPER FUNCTION: returns last node.
    private Node<E> last(){
	if(this.head == null){
	    return null;
	}
	Node<E> result = this.head;
	while(result.getNext() != null){
	    result = result.getNext();
	}
	return result;
    }

    // HELPER FUNCTION: returns node at passed index.
    private Node<E> getNode(int index){
	if(size <= index){
	    System.out.println("Invalid index.");
	    return null;
	}
	Node<E> result = this.head;
	int current = 0;
	while(current < index){
	    result = result.getNext();
	    current++;
	}
	return result;
    }

    // Creates a list from an array of objects.
    public MyLinkedList(E[] objects){
	int arraySize = objects.length;
	for(int i = 0; i < arraySize; i++){
	    addLast(objects[i]);
	}
	this.size = arraySize;
    }
    
    // Returns true if list contains no elements.
    public boolean isEmpty(){
	return this.size == 0;
    }

    // Returns number of elements in list.
    public int size(){
	return this.size;
    }
    
    // Returns the head element in list.
    public E getFirst(){
	if(this.head == null){
	    return null;
	}
	return this.head.getData();
    }

    // Returns the last element in list.
    public E getLast(){
	Node<E> result = last();
	if(result == null){
	    return null;
	}
	return result.getData();
    }

    // Adds element to beginning of list.
    public void addFirst(E e){
	Node<E> newHead = new Node<E>(e);
	newHead.setNext(this.head);
	this.head = newHead;
	this.size++;
    }
    
    // Adds element to end of list.
    public void addLast(E e){
	Node<E> newLast = new Node<E>(e);
	if(isEmpty()){
	    this.head = newLast;
	    this.size++;
	}else{
	    last().setNext(newLast);
	    this.size++;
	}
    }

    // Inserts element after specified index in list.
    public void add(int index, E e){
	Node<E> newNode = new Node<E>(e);
	Node<E> currentNode = getNode(index);
	newNode.setNext(currentNode.getNext());
	currentNode.setNext(newNode);
	this.size++;
    }
    
    // Removes head node and returns the object within removed node.
    public E removeFirst(){
	if(isEmpty()){
	    System.out.println("List is already empty.");
	    return null;
	}
	Node<E> result = this.head;
	this.head = this.head.getNext();
	this.size--;
	return result.getData();
    }

    // Removes last node and returns the object within removed node.
    public E removeLast(){
	if(isEmpty()){
	    System.out.println("List is already empty.");
	    return null;
	}
	Node<E> result = last();
	getNode(this.size - 2).setNext(null);
	this.size--;
	return result.getData();
    }

    // Removes element at specified position in list.
    public E remove(int index){
	if(index == 0){
	    return removeFirst();
	}
	Node<E> result = getNode(index);
	getNode(index - 1).setNext(result.getNext());
	this.size--;
	return result.getData();
    }
    
    // Removes first occurence of specified element, returns true if removed.
    public boolean remove(E e){
	int index = indexOf(e);
	if(index == -1){
	    return false;
	}
	remove(index);
	return true;	
    }

    // Clears the list.
    public void clear(){
	this.head = null;
	this.tail = null;
	this.size = 0;
    }

    // Returns true if list contains specified element.
    public boolean contains(Object o){
	if(indexOf(o) == -1){
	    return false;
	}
	return true;
    }
    
    // Returns element at specified index in list.
    public E get(int index){
	return getNode(index).getData();
    }

    // Returns index of first matching element in list, -1 if no match.
    public int indexOf(Object o){
	Node<E> result = this.head;
	int index = 0;
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
    public int lastIndexOf(Object o){
	Node<E> result = this.head;
	int index = 0;
	int lastIndex = -1;
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
    public E set(int index, E e){
	getNode(index).setData(e);
	return getNode(index).getData();
    }
	    
	

}

// Individual node consists of a piece of data and a reference to another node.
class Node<E>{
   
    private E data;
    private Node<E> next;

    // Node constructor 
    public Node(E newData){
	this.data = newData;
	this.next = null;
    }

    // Modifies data field in node.
    public void setData(E data){
	this.data = data;
    }

    // Modifies next field in node.
    public void setNext(Node<E> next){
	this.next = next;
    }

    // Returns data field.
    public E getData(){
	return data;
    }

    // Returns next field.
    public Node<E> getNext(){
	return next;
    }
}

public class Lab8 {

    public static void main(String[] args){
	System.out.println("===============================================");
	System.out.println("Demonstration of MyLinkedList.");
	System.out.println("===============================================");

	System.out.println("Testing default list constructor.");
	System.out.println("  Creating empty integer list...");
	MyLinkedList<Integer> list1 = new MyLinkedList<Integer>();	
	System.out.print("  List 1: ");
	displayList(list1);
	System.out.println("Testing array list constructor.");
	System.out.println("  Creating list from array of strings...");
	String[] array = new String[7];
	array[0] = "R";
	array[1] = "e";
	array[2] = "v";
	array[3] = "i";
	array[4] = "v";
	array[5] = "a";
	array[6] = "l";
	MyLinkedList<String> list2 = new MyLinkedList<String>(array);
	System.out.print("  List 2: ");
	displayList(list2);

	System.out.println("Testing isEmpty boolean.");
	System.out.println("  Value of list1.isEmpty(): " + list1.isEmpty());
	System.out.println("  Value of list2.isEmpty(): " + list2.isEmpty());

	System.out.println("Testing size return function.");
	System.out.println("  Value of list1.size(): " + list1.size());
	System.out.println("  Value of list2.size(): " + list2.size());

	System.out.println("Testing head return function.");
	System.out.println("  Value of list1.getFirst(): " + list1.getFirst());
	System.out.println("  Value of list2.getFirst(): " + list2.getFirst());

	System.out.println("Testing last return function.");
	System.out.println("  Value of list1.getLast(): " + list1.getLast());
	System.out.println("  Value of list2.getLast(): " + list2.getLast());

	System.out.println("Testing addFirst function.");
	System.out.println("  Adding '1' to List 1.");
	list1.addFirst(1);
	System.out.print("  List 1: ");
	displayList(list1);
	System.out.println("  Adding 'The ' to List 2.");
	list2.addFirst("The ");
	System.out.print("  List 2: ");
	displayList(list2);

	System.out.println("Testing addLast function.");
	System.out.println("  Adding '3' to List 1.");
	list1.addLast(3);
	System.out.print("  List 1: ");
	displayList(list1);
	System.out.println("  Adding ' Jesus' to List 2.");
	list2.addLast(" Jesus");
	System.out.print("  List 2: ");
	displayList(list2);

	System.out.println("Testing add function.");
	System.out.println("  Adding '2' after element 0 of List 1.");
	list1.add(0, 2);
	System.out.print("  List 1: ");
	displayList(list1);
	System.out.println("  Adding ' of' after element 7 of List 2.");
	list2.add(7, " of");
	System.out.print("  List 2: ");
	displayList(list2);

	System.out.println("Testing removeFirst function.");
	System.out.println("  Removed: " + list1.removeFirst());
	System.out.print("  List 1: ");
	displayList(list1);
	System.out.println("  Removed: " + list2.removeFirst());
	System.out.print("  List 2: ");
	displayList(list2);

	System.out.println("Testing removeLast function.");
	System.out.println("  Removed: " + list1.removeLast());
	System.out.print("  List 1: ");
	displayList(list1);
	System.out.println("  Removed: " + list2.removeLast());
	System.out.print("  List 2: ");
	displayList(list2);

	System.out.println("Testing boolean-remove function.");
	System.out.println("Also tests indexOf and index-remove functions.");
	System.out.println("  Removed 'a' from list 2: " + list2.remove("a"));
	System.out.print("  List 2: ");
	displayList(list2);

	System.out.println("Testing boolean-contains function.");
	System.out.println("  'a' is in list 2: " + list2.contains("a"));
	System.out.println("  'v' is in list 2: " + list2.contains("v"));

	System.out.println("Testing get function.");
	System.out.println("  Element 4 in list 2: " + list2.get(4));

	System.out.println("Testing last-indexOf function.");
	System.out.println("  LastIndexOf 'v': " + list2.lastIndexOf("v"));

			   
	System.out.println("Testing set function.");
	System.out.println("  Changing Element 4 to 'a'.");
	list2.set(4, "a");
	System.out.print("  List 2: ");
	displayList(list2);

	System.out.println("Testing clear function.");
	System.out.println("  Clearing list 2.");
	list2.clear();
	System.out.print("  List 2: ");
	displayList(list2);


	System.out.println("All functions appear to be working.");
    }

    public static void displayList(MyLinkedList list){
	int listSize = list.size();
	for(int i = 0; i < listSize; i++){
	    System.out.print("|" + list.get(i));
	}
	System.out.print("| \n");
    }

}
