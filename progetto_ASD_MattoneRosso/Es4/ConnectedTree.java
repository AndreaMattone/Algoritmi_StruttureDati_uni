import java.io.*;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.ArrayList;
import java.util.Queue;
import java.util.Scanner;

public class ConnectedTree {
    int vertices;
    int maxWeight;
    List<List<Node>> nodeList;
    ArrayList<Node> tree;
    int query[][];
    int numInterrogations;
    static int counter=0;
    static Integer precNode;

    static class Node{ /*Elemento della linkedList*/
        int name;
        int weight;
        public Node(int n,int w){
            name=n;
            weight=w;
        }
    }
    public ConnectedTree(){
        this.vertices = 100000; //Inizialmente vengono creati 100000 puntatori a Node
        this.maxWeight = -1;
        nodeList = new ArrayList<List<Node>>();
        tree = new ArrayList<Node>(vertices);
        for (int i = 0; i <vertices ; i++) {
            nodeList.add(new ArrayList<Node>());
            tree.add(i,null);
        }
    }

    public void loadFile(){
        int Node1,Node2,weight;
        String[] row;
        int counter;
        String line;

        Scanner scan = new Scanner(System.in);
        vertices = Integer.valueOf(scan.nextLine());

        counter = vertices-1; //Il numero di archi è N-1 nodi
        while(counter>0){
            line = scan.nextLine();
            row = line.split(" ");
            Node1 = Integer.valueOf(row[0]);
            Node2 = Integer.valueOf(row[1]);
            weight = Integer.valueOf(row[2]);
            maxWeight = weight>maxWeight?weight:maxWeight; //Registro il peso se è il massimo
            nodeList.get(Node1-1).add(0,new Node(Node2-1,weight));//Inserisco il nodo da entrambe le parti della linkedlist
            nodeList.get(Node2-1).add(0,new Node(Node1-1,weight));
            counter--;
        }
        counter=0;
        line= scan.nextLine();
        if(line!=null){ //Se ci sono interrogazioni
            numInterrogations = Integer.valueOf(line);
            query = new int[numInterrogations][3];
            while(counter<numInterrogations){
                line = scan.nextLine();
                row = line.split(" ");
                Node1 = Integer.valueOf(row[0]);
                Node2 = Integer.valueOf(row[1]);
                weight = Integer.valueOf(row[2]);
                query[counter][0] = Node1;
                query[counter][1] = Node2;
                query[counter][2] = weight;
                counter++;
            }
        }
        scan.close();
    }
    /***************** Metodi per capire se il grafo è connesso ***************************/
    public void bfs(){ //Tramite la bfs creo l'albero
        boolean visited[] = new boolean[vertices];

        Queue<Integer> queue = new LinkedList<Integer>();
        tree.set(0,new Node(0,Integer.MAX_VALUE)); //Questa è la radice, unico nodo con nome uguale a se stesso e peso massimo
        queue.add(0);
        visited[0] = true;
        precNode = 0;
        while(!queue.isEmpty()) {
            Integer node = queue.remove();
            Integer child=null;
            while((child=getUnvisitedChildNode(node,visited))!=null) {
                visited[child]=true;
                tree.set(child,new Node(node,existElement(node,child))); //Aggiungo un nodo con nome node, ovvero il genitore, e come peso quello dell'arco
                queue.add(child);
            }
        }
        counter=0;
    }
    //Restituisce il prossimo vicino di node da visitare
    public Integer getUnvisitedChildNode(Integer node,boolean visited[]){
        if(precNode!=node){ //Se mi trovo in un nuovo nodo
            counter=0;  //Azzero l'indice che conta il numero di vicino a cui sono arrivato
            precNode=node; //Aggiorno il nodo a quello corrente
        }
        for(;counter<nodeList.get(node).size();counter++){ //Continuo a visitare vicinio da dove sono arrivato
            if(visited[nodeList.get(node).get(counter).name] == false)
                return nodeList.get(node).get(counter).name;
        }
        return null;
    }
    public int existElement(int indexSubList,int Node){
        Node temp;
        for(int index=0;index<nodeList.get(indexSubList).size();index++){
            temp = nodeList.get(indexSubList).get(index);
            if(temp.name==Node)
                return  temp.weight;
        }
        return -1;
    }
    /********************************************************/
    /**************** Esecuzione test **********************/
    public void test(){
        int numTest=0;
        double percentage;

        bfs();
        for(int i=0;i<numInterrogations;i++){
            numTest++;
            System.out.println(process(query[i][0],query[i][1],query[i][2]));
        }
    }
    public boolean checkParent(int source,int destination,int weight){ //Risalgo l'albero per rimuovere i possibili archi
        int current = source;
        Node temp = tree.get(source);
        Node temp1 = tree.get(destination);

        if(temp.name==temp1.name){ //Genitore in comune
            if(temp.weight < weight || temp1.weight<weight)
                return true;
            else
                return false;
        } 
        while(temp.name!=destination && temp.name!=current && temp.weight>=weight){ //fin quando non raggiungo la destinazione, la radice o
                                                                                    // l'arco è maggiore di quello che voglio sostituire
            current = temp.name;
            temp = tree.get(current);
        }
        if(temp.weight<weight)
            return true;
        else
            return false;
    }
    public String process(int Node1,int Node2,int weight){
        boolean esc = false;
        int weightExist=-1;

        if(tree.get(Node1-1).name == (Node2-1) || tree.get(Node2-1).name == (Node1-1)){  //se un nodo è figlio dell'altro memorizzo il peso dell'arco
            if(tree.get(Node1-1).name == (Node2-1))
                weightExist = tree.get(Node1-1).weight; //memorizzo il peso dell'arco
            else
                weightExist = tree.get(Node2-1).weight;
        }
        if(weight<maxWeight){
            if (weightExist!=-1){ //se esiste un arco tra padre e figlio
                if(weightExist<weight)
                    return "YES";
                else
                    return "NO";
            }            
            else
                esc = checkParent(Node1-1,Node2-1,weight) || checkParent(Node2-1,Node1-1,weight); //Risalgo l'albero da entrambi i nodi
        }            

        return esc==true?"YES":"NO";
    }
    public static void main(String[] args) {
        ConnectedTree c = new ConnectedTree();
        c.loadFile();
        c.test();
    }
}