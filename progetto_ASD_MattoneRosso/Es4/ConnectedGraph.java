import java.io.*;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.ArrayList;
import java.util.Queue;
import java.util.Scanner;

public class ConnectedGraph {
    int vertices;
    int maxWeight;
    List<List<Node>> nodeList;
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
    public ConnectedGraph(){
        this.vertices = 100000; //Inizialmente vengono creati 100000 puntatori a Node
        this.maxWeight = -1;
        nodeList = new ArrayList<List<Node>>();
        for (int i = 0; i <vertices ; i++) {
            nodeList.add(new ArrayList<Node>());
        }
    }

    public List<List<Node>> getNodeList() {
        return nodeList;
    }

    public void setNodeList(List<List<Node>> nodeList) {
        this.nodeList = nodeList;
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
    public boolean bfs(){
        boolean visited[] = new boolean[vertices];
        boolean visited2[] = new boolean[vertices];

        Arrays.fill(visited2,true);
        Queue<Integer> queue = new LinkedList<Integer>();
        queue.add(0);
        visited[0] = true;
        precNode = 0;
        while(!queue.isEmpty()) {
            Integer node = queue.remove();
            Integer child=null;
            while((child=getUnvisitedChildNode(node,visited))!=null) {
                visited[child]=true;
                queue.add(child);
            }
        }
        counter=0;
        return Arrays.equals(visited,visited2);
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
    public int indexElement(int indexSubList,int Node, int weight){
        Node temp;
        for(int index=0;index<nodeList.get(indexSubList).size();index++){
            temp = nodeList.get(indexSubList).get(index);
            if(temp.name==Node && temp.weight==weight)
                return index;
        }
        return -1;
    }
    /********************************************************/
    /**************** Esecuzione test **********************/
    public void test(){
        int numTest=0;
        double percentage;

            for(int i=0;i<numInterrogations;i++){
                numTest++;
                   System.out.println(process(query[i][0],query[i][1],query[i][2]));
            }
    }
    public String process(int Node1,int Node2,int weight) {
        boolean esc = false;

        if(weight>maxWeight) //Non può diminuire il peso del grafo
            return "NO";

        for (int i = 0; i < vertices; i++) {
            for (int k=0;k<nodeList.get(i).size();k++) { //Essendo in copy l'arco della query non c'è
                Node n = nodeList.get(i).get(k);
                if(n.weight>weight){
                    //Rimuovo il vertice i-esimo
                    nodeList.get(i).remove(n);
                    nodeList.get(n.name).remove(indexElement(n.name,i,n.weight));
                    /*Rimuovo un arco e verifico che il grafo sia connesso,
                        se non lo è continuo, altrimenti il test ha successo*/
                    //Aggiungo arco della query al fondo della lista
                    nodeList.get(Node1-1).add(0,new Node(Node2-1,weight));
                    nodeList.get(Node2-1).add(0,new Node(Node1-1,weight));

                    if(nodeList.get(i).size()>0 && nodeList.get(n.name).size()>0)
                        esc = bfs();
                        //esc=true;
                    else
                        esc=false;

                    //Rimuovo la modifica
                    nodeList.get(Node1-1).remove(0);
                    nodeList.get(Node2-1).remove(0);
                    nodeList.get(i).add(0,n);
                    nodeList.get(n.name).add(0,new Node(i,n.weight));

                    if(esc)
                        return "YES";
                }
            }
        }

        return "NO";
    }
    public static void main(String[] args) {
        ConnectedGraph c = new ConnectedGraph();
        c.loadFile();
        c.test();
    }
}