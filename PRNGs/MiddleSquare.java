/*
 *  Copyright (C) 2013 Rafael Rendón Pablo <smart.rendon@gmail.com>
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

public class MiddleSquare {
  public static void main(String[] args)
  {

    if (args.length != 2) {
      System.out.println("Usage: java MiddleSquare <seed> <n>");
      System.exit(0);
    }

    long seed = Long.parseLong(args[0]);
    int n = Integer.parseInt(args[1]);
    int k = args[0].length();
    System.out.println("k = " + k);

    for (int i = 0; i < n; i++) {
      seed *= seed;
      String digits = String.valueOf(seed);
      while (digits.length() < k + k) // Add leading zeros
        digits = "0" + digits;

      if (k%2 == 1)
        digits = "0" + digits;

      String center = "";
      int l = (digits.length() - k)/2;
      int r = l + k;
      for (int j = l; j < r; j++)
        center += digits.charAt(j);

      System.out.println(center);
      seed = Long.parseLong(center);
    }
  }
}

