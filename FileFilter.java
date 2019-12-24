package test;

import java.io.File;
import java.io.FileWriter;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;
public class FileFilter {
   public static void main(String args[]) throws Exception {
      Scanner in = new Scanner(System.in);
      System.out.println("Enter File name to filter");
      String filename=in.next();
      
      String filePath = ".//"+filename;
      String input = null;
      //Instantiating the Scanner class
      Scanner sc = new Scanner(new File(filePath));
      //Instantiating the FileWriter class
      FileWriter writer = new FileWriter(".//"+filename+"MOD"+".c");
      //Instantiating the Set class
      Set set = new HashSet();
      while (sc.hasNextLine()) {
         input = sc.nextLine();
         if(set.add(input)) {
            writer.append(input+"\n");
         }
      }
      writer.append("\n}");
      writer.flush();
      System.out.println("Contents added in "+filename+"MOD.c"+" ............");
   }
}
