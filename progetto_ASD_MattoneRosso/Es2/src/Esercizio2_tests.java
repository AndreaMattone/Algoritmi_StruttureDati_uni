import static org.junit.Assert.assertEquals;

import org.junit.BeforeClass;
import org.junit.Test;

import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class Esercizio2_tests{
  private static Esercizio2 tester;

  @BeforeClass
  public static void testSetup() {
	    tester = new Esercizio2();
	  }

  /*Test edit distance*/
  @Test
  public void test_edit_distance_min(){

    System.out.println("test on distance min");
    tester.initializeMatrix("casa","cassa");
    assertEquals(1,tester.edit_distance_dyn("casa","cassa"));
    tester.initializeMatrix("casa","cara");
    assertEquals(2,tester.edit_distance_dyn("casa","cara"));
    tester.initializeMatrix("vinaio","vino");
    assertEquals(2,tester.edit_distance_dyn("vinaio","vino"));
    tester.initializeMatrix("tassa","passato");
    assertEquals(4,tester.edit_distance_dyn("tassa","passato"));
    tester.initializeMatrix("pioppo","pioppo");
    assertEquals(0,tester.edit_distance_dyn("pioppo","pioppo"));
  }

  /*Test a total edit distance*/
  @Test
  public void test_edit_distance_max(){
    System.out.println("test on distance max");
    tester.initializeMatrix("casa","topo");
    assertEquals(8,tester.edit_distance_dyn("casa","topo"));
  }

  /*Test limit cases*/
  @Test
  public void test_edit_distance_lim(){
    System.out.println("test on limit cases");
    tester.initializeMatrix("casa","");
    assertEquals(4,tester.edit_distance_dyn("casa",""));
    tester.initializeMatrix("","casa");
    assertEquals(4,tester.edit_distance_dyn("","casa"));
  }

  public static void main(String[] args) {
    Result result = JUnitCore.runClasses(Esercizio2_tests.class);
    for (Failure failure : result.getFailures()){
      System.out.println("Test Failed...\n");
      System.out.println(failure.toString());
    }
    System.out.println("Test Successed...\n");
    System.out.println(result.wasSuccessful());
  }
}