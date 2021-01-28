import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import java.util.Collections;

public class Esercizio2 {
  private String s1;
  private String s2;
  private int matrix[][];
  private ArrayList<String> correctList,dictionaryList;

  /*Constructor*/
  public Esercizio2(String s1,String s2){
    int maxlength = Integer.max(s1.length(),s2.length());
    if(maxlength==0) {
      throw new Error("USAGE: at least one of the two strings must be initialized");
    }
    this.s1 = s1;
    this.s2 = s2;
    this.matrix = new int[maxlength][maxlength];
    for(int[] row:matrix) {
      Arrays.fill(row, -1);
    }
  }

  /*Empty Constructor*/
  public Esercizio2(){
    this.s1="";
    this.s2="";
    this.matrix=null;
  }

  /*Initialize matrix -1*/
  public void initializeMatrix(String s1,String s2){
    int maxlength = Integer.max(s1.length(),s2.length());
    this.matrix = new int[maxlength][maxlength];
    for(int[] row:matrix) {
      Arrays.fill(row, -1);
    }
  }

  /*Return string S1*/
  public String getS1(){
    return this.s1;
  }
  /*Return string S2*/
  public String getS2(){
    return this.s2;
  }
  /*Get the correctme list*/
  public ArrayList<String> getCorrectList(){
    return correctList;
  }
  /*Get the dictionary list*/
  public ArrayList<String> getDictionaryList(){
    return dictionaryList;
  }

  /*Return the substring of s ignoring the first character*/
  public String rest(String s){
    return s.substring(1,s.length());
  }

  /*Return the edit_distance between S1 and S2*/
  public int edit_distance(String s1,String s2){
    int temp;
    if(Integer.min(s1.length(),s2.length())==0){
      return Integer.max(s1.length(),s2.length());
    }
    if(s1.charAt(0) != s2.charAt(0)) {
      temp = Integer.MAX_VALUE;
    }else{
      temp = edit_distance(rest(s1),rest(s2));
    }
    return Integer.min(temp,Integer.min(edit_distance(s1,rest(s2))+1,edit_distance(rest(s1),s2)+1)); //min(d_no-op,d_canc,d_ins)
  }

  /*Return the edit_distance between S1 and S2, Dynamic version*/
  public int edit_distance_dyn(String s1,String s2){
    int assign,temp;
    if(Integer.min(s1.length(),s2.length())==0) {
      return Integer.max(s1.length(), s2.length());
    }else{
      if(matrix[s1.length()-1][s2.length()-1]!=-1) {
        return matrix[s1.length() - 1][s2.length() - 1];
      }else{
        if(s1.charAt(0) != s2.charAt(0)) {
          temp = Integer.MAX_VALUE;
        }else{
          temp = edit_distance_dyn(rest(s1),rest(s2));
        }
        assign = Integer.min(temp,Integer.min(edit_distance_dyn(s1,rest(s2))+1,edit_distance_dyn(rest(s1),s2)+1)); //min(d_no-op,d_canc,d_ins)
      }
    }
    matrix[s1.length()-1][s2.length()-1] = assign;
    return assign;
  }

  /*Read file*/
  public void readFile(String fn1,String fn2){
    correctList = new ArrayList<String>();
    dictionaryList = new ArrayList<String>();
    String temp;
    try {
      File myObj = new File(fn1);
      Scanner myReader = new Scanner(myObj);
      while (myReader.hasNext()) {
        temp = myReader.next();
        temp = temp.replaceAll("\\p{P}","");
        correctList.add(temp);
      }
      myReader.close();
    } catch (FileNotFoundException e) {
      System.out.println("An error occurred.");
      e.printStackTrace();
    }
    try {
      File myObj = new File(fn2);
      Scanner myReader = new Scanner(myObj);
      while (myReader.hasNext()) {
        dictionaryList.add(myReader.next());
      }
      myReader.close();
    }catch (FileNotFoundException e) {
      System.out.println("An error occurred.");
      e.printStackTrace();
    }
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    Esercizio2 es = new Esercizio2();
    es.readFile("correctme.txt","dictionary.txt");
        
    ArrayList<Integer> distanze =null;//[es.getdictionaryListsize()];
    ArrayList<String> corrList = es.getCorrectList();
    ArrayList<String> dictList = es.getDictionaryList();

    for(int i=0;i<corrList.size();i++){
      distanze = new ArrayList<Integer>();
      for(int j=0;j<dictList.size();j++){
        es.initializeMatrix(corrList.get(i),dictList.get(j));
        distanze.add(es.edit_distance_dyn(corrList.get(i),dictList.get(j)));
      }
      int minValue = Collections.min(distanze);
      System.out.println("\nParola: "+ corrList.get(i)+"\n\n");
      for(int k=0;k<dictList.size();k++){
        if(distanze.get(k)==minValue)
        System.out.println(dictList.get(k));
      }
    }
  }
}
