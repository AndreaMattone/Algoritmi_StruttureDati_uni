import java.io.*;
import java.util.Arrays;
import java.util.LinkedList;

public class Graph {
    int numVertices;
    int numInterrogations;
    int maxWeight;
    LinkedList<Node> nodeList [];
    int query[][];


    final static String FILEMYTEST = "MiniTest/input.txt";
    final static String FILERESULTMYTEST = "MiniTest/correct.txt";

    final static String FILETEST1 = "test1/input.txt";
    final static String FILETEST2 = "test2/input.txt";
    final static String FILETEST3 = "test3/input.txt";
    final static String FILETEST4 = "test4/input.txt";
    final static String FILETEST5 = "test5/input.txt";
    final static String FILETEST6 = "test6/input.txt";
    final static String FILETEST7 = "test7/input.txt";
    final static String FILETEST8 = "test8/input.txt";
    final static String FILETEST9 = "test9/input.txt";
    final static String FILETEST10 = "test10/input.txt";
    final static String FILETEST11 = "test11/input.txt";
    final static String FILERESULT1 = "test1/correct.txt";
    final static String FILERESULT2 = "test2/correct.txt";
    final static String FILERESULT3 = "test3/correct.txt";
    final static String FILERESULT4 = "test4/correct.txt";
    final static String FILERESULT5 = "test5/correct.txt";
    final static String FILERESULT6 = "test6/correct.txt";
    final static String FILERESULT7 = "test7/correct.txt";
    final static String FILERESULT8 = "test8/correct.txt";
    final static String FILERESULT9 = "test9/correct.txt";
    final static String FILERESULT10 = "test10/correct.txt";
    final static String FILERESULT11 = "test11/correct.txt";

    static class Node{ /*Elemento della linkedList*/
        int name;
        int weight;
        public Node(int n,int w){
            name=n;
            weight=w;
        }
    }

    public Graph(int vertices){
        this.numVertices = vertices;
        nodeList = new LinkedList[vertices];
        for (int i = 0; i <vertices ; i++) {
            nodeList[i] = new LinkedList<Node>();
        }
    }


    public void loadData(String filepath){
        int Node1,Node2,weight;
        String[] row;
        int counter;
        try(BufferedReader br = new BufferedReader(new FileReader(filepath))) {
            String line = br.readLine();
            if(line != null){
                numVertices = Integer.parseInt(line);;
                counter = numVertices-1;
                while(counter>0){
                    line = br.readLine();
                    row = line.split(" ");
                    Node1 = Integer.parseInt(row[0]);
                    Node2 = Integer.parseInt(row[1]);
                    weight = Integer.parseInt(row[2]);
                    maxWeight = weight>maxWeight?weight:maxWeight; //Registro il peso se è il massimo
                    nodeList[Node1-1].addFirst(new Node(Node2-1,weight)); //Inserisco il nodo da entrambe le parti della linkedlist
                    nodeList[Node2-1].addFirst(new Node(Node1-1,weight));
                    counter--;
                }
                counter=0;
                line= br.readLine();
                if(line!=null){
                    numInterrogations = Integer.parseInt(line);
                    query = new int[numInterrogations][3];
                    while(counter<numInterrogations){
                        line = br.readLine();
                        row = line.split(" ");
                        Node1 = Integer.parseInt(row[0]);
                        Node2 = Integer.parseInt(row[1]);
                        weight = Integer.parseInt(row[2]);
                        query[counter][0] = Node1;
                        query[counter][1] = Node2;
                        query[counter][2] = weight;
                        counter++;
                    }
                }
                br.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }


    }

    public int indexElement(int indexSubList,int Node, int weight){
        Node temp;
        for(int index=0;index<nodeList[indexSubList].size();index++){
            temp = nodeList[indexSubList].get(index);
            if(temp.name==Node && temp.weight==weight)
                return index;
        }
        return -1;
    }



    public void DFS(int source, LinkedList<Node> tempList [],boolean[] visited ){
        visited[source] = true;

        for(int i=0;i<tempList[source].size(); i++){
            int neighbor = tempList[source].get(i).name;
            if(visited[neighbor]==false){ //Se non è ancora stato visitato
                //visito ricorsivamente il vicino passando la sua lista
                DFS(neighbor, tempList, visited);
            }
        }

    }


    public boolean isConnected(LinkedList<Node>[] list){
        int vertices = numVertices;
        LinkedList<Node> tempList[] = list;

        boolean[] visited = new boolean[vertices];


        DFS(0,tempList,visited);

        int count = 0;
        for (int i = 0; i <visited.length ; i++) {
            if(visited[i]==true)
                count++;
        }
        if(vertices==count){
            return true;
        }else{
            return false;
        }




    }



    public String process(int Node1,int Node2,int weight) {
        boolean esc = false;
        LinkedList<Node>[] copy = (LinkedList<Node>[]) nodeList.clone();


        if(weight>maxWeight) { //Non può diminuire il peso del grafo
            return "NO";
        }

        for (int i = 0; i < numVertices; i++) {
            for (int k=0;k<copy[i].size();k++) { //Essendo in copy l'arco della query non c'è



                Node n = copy[i].get(k);
                if(n.weight>weight){

                    //Rimuovo il vertice i-esimo
                    copy[i].remove(n);
                    copy[n.name].remove(indexElement(n.name,i,n.weight));
                    /*Rimuovo un arco e verifico che il grafo sia connesso,
                        se non lo è continuo, altrimenti il test ha successo*/

                    //Aggiungo arco della query al fondo della lista
                    copy[Node1-1].addFirst(new Node(Node2-1,weight));
                    copy[Node2-1].addFirst(new Node(Node1-1,weight));

                    if(copy[i].size()>0 && copy[n.name].size()>0){
                        esc = isConnected(copy);
                    }
                    //esc = isConnected(nodeList);

                    //Rimuovo la modifica
                    copy[Node1-1].removeFirst();
                    copy[Node2-1].removeFirst();
                    copy[i].addFirst(n);
                    copy[n.name].addFirst(new Node(i,n.weight));

                    if(esc){
                        return "YES";
                    }

                }


            }
        }



        return "NO";
    }




    public void test(){
        int numTest=0;
        System.out.println(numInterrogations + " tests");
        try {
            BufferedWriter bw = new BufferedWriter(new FileWriter("output.txt"));
            for(int i=0;i<numInterrogations;i++){
                numTest++;
                System.out.println(numTest);
                bw.write(process(query[i][0],query[i][1],query[i][2])+"\n"); //Stampa esisto di ciascuna query
            }
            bw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    private static int isEqual(String f1, String f2){
        int counter=0;
        int lineno=0;
        String row1,row2;
        try{
            BufferedReader br1 = new BufferedReader(new FileReader(f1));
            BufferedReader br2 = new BufferedReader(new FileReader(f2));

            while((row1=br1.readLine())!=null && (row2=br2.readLine())!=null){
                lineno++;
                if(!row1.equals(row2)){
                    counter++;
                    System.out.println(lineno + " " + row1 + " " + row2);
                }

            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return counter;
    }

    public static void main(String[] args) {

        int vertices = 0;
        Graph myGraph;

       /* try(BufferedReader brTemp2 = new BufferedReader(new FileReader(FILEMYTEST))) {
            String line = brTemp2.readLine();
            vertices = Integer.parseInt(line);
        } catch (IOException e) {
            e.printStackTrace();
        }
        myGraph = new Graph(vertices);
        myGraph.loadData(FILEMYTEST);
        System.out.print("Mytest: ");
        myGraph.test();
        System.out.println("-> " + isEqual(FILERESULTMYTEST,"output.txt") + " dismatch");*/


        try(BufferedReader brTemp2 = new BufferedReader(new FileReader(FILETEST3))) {
            String line = brTemp2.readLine();
            vertices = Integer.parseInt(line);
        } catch (IOException e) {
            e.printStackTrace();
        }
        myGraph = new Graph(vertices);
        myGraph.loadData(FILETEST3);
        System.out.print("Test 3: ");
        myGraph.test();
        System.out.println("-> " + isEqual(FILERESULT3,"output.txt") + " dismatch");

    }











}
