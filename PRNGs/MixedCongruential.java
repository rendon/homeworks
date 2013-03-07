/*
 * Mixed Congruential Method.
 * This class implements the Mixed Congruential method, a
 * Pseudo Random Number Generator(PRNG). Them method is as follows:
 *
 *  X_n+1 = (a * X_n + c) % m
 *
 *  X_0 = the seed or start value
 *
 *  Where "%" is the modulus operator, i.e. the reminder of an integer division.
 *
 *  Constraints:
 *  X_0 >= 0 
 *  a   >= 0
 *  c >= 0
 *  m > X_0, m > a, m > c
 *
 *  Period length:
 *  The period(number of diferent pseudo-random numbers) of this method is at
 *  most m, in some cases much less.
 *
 *  Constraints to get periods of length m:
 *  I)    c is relatively prime to m
 *  II)   m = p1 * ... * pn where p1, ..., pn are primes => a(mod p1) = ... = a(mod pn) = 1
 *  III)  m is divided by 4 => a(mod 4) = 1 
 *  
*/

public class MixedCongruential {
  public static final int MAX_M = 1000000;
  private long seed;
  private long modulus;
  private long multiplier;
  private long increment;
  private long initialSeed;
  private long nextNumber;
  private boolean hasNextNumber;
  private boolean[] X; 


  /**
   * Constructor.
   * @param x0 the "seed" or "start value"
   * @param a the "multiplier"
   * @param c the "increment"
   * @param m the "modulus"
  */
  public MixedCongruential(long x0, long a, long c, long m)
  {
    setSeed(x0);
    setInitialSeed(-1);
    setMultiplier(a);
    setIncrement(c);
    setModulus(m);

    X = new boolean[MAX_M];
    for (int i = 0; i < MAX_M; i++)
      X[i] = false;

    nextNumber = generateNext();
    X[(int)nextNumber] = true;
    hasNextNumber = true;
  }

  public boolean hasNext()
  {
    return hasNextNumber;
  }

  private long generateNext()
  {
    return (multiplier * seed + increment) % modulus;
  }

  public long next()
  {
    long x = nextNumber;
    seed = x;
    nextNumber = generateNext();

    if (X[(int)nextNumber])
      hasNextNumber = false;
    else
      X[(int)nextNumber] = true;
    
    return x;
  }

  public void setSeed(long x0)
  {
    seed = x0;
  }

  public long getSeed()
  {
    return seed;
  }

  private void setInitialSeed(long s)
  {
    initialSeed = s;
  }

  private long getInitialSeed() 
  {
    return initialSeed;
  }

  public void setMultiplier(long a)
  {
    multiplier = a;
  }

  public long getMultiplier()
  {
    return multiplier;
  }

  public void setIncrement(long c)
  {
    increment = c;
  }

  public long getIncrement() 
  {
    return increment;
  }

  public void setModulus(long m)
  {
    modulus = m;
  }

  public long getModulus() 
  {
    return modulus;
  }
}

