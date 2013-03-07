public class Test {
  public static void main(String[] args)
  {
    if (args.length != 4) {
      System.err.println("Usage: java Test <seed> <multiplier> <increment> <modulus>");
      System.exit(1);
    }

    long x0 = Long.parseLong(args[0]);
    long a = Long.parseLong(args[1]);
    long c = Long.parseLong(args[2]);
    long m = Long.parseLong(args[3]);

    MixedCongruential mc = new MixedCongruential(x0, a, c, m);

    int count = 0;

    while (mc.hasNext()) {
      System.out.print(mc.next() + " ");
      count++;
    }

    System.out.println();
    System.out.println("count = " + count);
  }

}

