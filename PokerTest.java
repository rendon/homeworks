/*
 *  Copyright (C) 2012 Rafael Rendón Pablo <smart.rendon@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

import java.io.*;

public class PokerTest {

  public static int[] countDigits(String hand)
  {
    int i;
    int[] D = new int[10];
    for (i = 0; i < 10; i++)
      D[i] = 0;

    for (i = 0; i < hand.length(); i++)
      D[hand.charAt(i) - '0']++;

    return D;
  }

  public static boolean allDiferent(String hand)
  {
    int i;
    int[] D = countDigits(hand);

    for (i = 0; i < 10; i++)
      if (D[i] > 1)
        return false;

    return true;
  }

  public static boolean onePair(String hand)
  {
    int i;
    int[] D = countDigits(hand);

    int pairs = 0;
    for (i = 0; i < 10; i++)
      if (D[i] == 2)
        pairs++;

    return pairs == 1;
  }


  
  public static boolean twoPairs(String hand)
  {
    int i;
    int[] D = countDigits(hand);

    int pairs = 0;
    for (i = 0; i < 10; i++)
      if (D[i] == 2)
        pairs++;

    return pairs == 2;
  }


  public static boolean threeOfAKind(String hand)
  {
    int i;
    int[] D = countDigits(hand);

    int tertiaries = 0;
    for (i = 0; i < 10; i++)
      if (D[i] == 3)
        tertiaries++;

    return tertiaries == 1;
  }


  // Tetiary and pair
  public static boolean fullHouse(String hand)
  {
    int i;
    int[] D = countDigits(hand);

    int pairs = 0;
    int tertiaries = 0;
    for (i = 0; i < 10; i++) {
      if (D[i] == 2)
        pairs++;
      if (D[i] == 3)
        tertiaries++;
    }

    return pairs == 1 && tertiaries == 1;
  }

  // Poker
  public static boolean fourOfAKind(String hand)
  {
    int i;
    int[] D = countDigits(hand);

    for (i = 0; i < 10; i++)
      if (D[i] == 4)
        return true;

    return false;
  }


  // Quitilla?
  public static boolean fiveOfAKind(String hand)
  {
    int i;
    int[] D = countDigits(hand);

    for (i = 0; i < 10; i++)
      if (D[i] == 5)
        return true;

    return false;
  }



  public static void main(String[] args) throws IOException
  {
    BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    String hand;

    int i, n = 0;
    int[] F = new int[7]; // F[0] = all different, F[6] = five of a kind
    String[] T = new String[] {"TD", "1P", "2P", "T ", "TP", "P ", "Q "};
    
    for (i = 0; i < 7; i++)
      F[i] = 0;

    System.out.println("TD = Todos Diferentes");
    System.out.println("1P = 1 Par");
    System.out.println("2P = 2 Pares");
    System.out.println("T  = Tercia");
    System.out.println("TP = Tercia y Par");
    System.out.println("P  = Poker");
    System.out.println("Q  = Quintilla");
    System.out.println();

    while ((hand = reader.readLine()) != null) {
      hand = hand.trim();
      String type = "";

      n++;
      
      if (fiveOfAKind(hand)) {
        F[6]++;
        type = T[6];
      } else if (fourOfAKind(hand)) {
        F[5]++;
        type = T[5];
      } else if (fullHouse(hand)) {
        F[4]++;
        type = T[4];
      } else if (threeOfAKind(hand)) {
        F[3]++;
        type = T[3];
      } else if (twoPairs(hand)) {
        F[2]++;
        type = T[2];
      } else if (onePair(hand)) {
        F[1]++;
        type = T[1];
      } else if (allDiferent(hand)) {
        F[0]++;
        type = T[0];
      }

      System.out.println(hand + " : " + type);
    }


    double[] P = new double[]{0.3024, 0.5040, 0.1080, 0.0720,
                              0.0090, 0.0045, 0.0001};
    double[] E = new double[7]; 
    double sum = 0;

    System.out.printf("\nC\tFO\t\tFE\t\t\t(FO - FE)^2/FE\n");
    System.out.println("-------------------------------------------------------" + 
                       "-----------------------------");
    for (i = 0; i < 7; i++) {
      E[i] = n * P[i];

      double square = Math.pow(E[i] - F[i], 2)/E[i];
      sum += square;

      System.out.printf("%s\t%d\t(%d*%f) = %f\t(%d-%f)^2/%f = %f\n",
                        T[i], F[i], n, P[i], E[i], F[i], E[i], E[i], square);
    }

    System.out.println("\nSumatoria = " + sum);
    
    String answer = "RECHAZADA";
    if (sum <= 12.592)  // Chi-square value with 6 DF and 95% of confidence
      answer = "ACEPTADA";
    System.out.println("\nLA COLLECCIÓN DE NÚMEROS ES: " + answer);
  }
}

