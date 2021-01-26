/*
Suppose we have a simple hash table that consists of a vector of integers. We can preallocate the table to have a specific size and fill the values with -1 to begin with, to mark those elements empty. For simplicity, this table will actually be a hash set rather than a hash map; in other words, rather than mapping unique keys to values, we simply have a collection of unique keys, so it is not a dictionary ADT. Such a table merely answers the question of whether any given integer is part of the set (can be found) or is not part of the set (cannot be found).

In the code below, you need to implement the insert function:

int insert(int value, std::vector<int> &table); 

This insert function should first compute a specific hash function of value. This hash function should return the least-significant three decimal digits (a number from 0 to 999) of the variable value. This hash result should be used as an index into the thousand-element vector table that has been previously initialized with -1 in each element. If the element at this location of table is available (currently set to -1), you can replace the element with value. If this location is not available (currently set to some other value than -1) then you should check the next element, repeatedly, until you find an available element and can store value there. The insert() function should then return the number of times a location in the hash table was identified to store the given value but was not available.

Example: If your function is able to insert the value in the hash location on the first try, return 0. If your function has to check the next two locations before finding an empty space, return 2.

The main() procedure below will create an appropriate table, then create 500 random values and call insert() on each one of them to insert them into the table. At the end, this procedure will report the length of the longest cluster encountered when inserting a value (as reported by your insert() function) and then print out the contents of the hash table so you can see how clusters form. Since the original hashed position will be the three least significant digits of the value stored there, it will be easy to see which values had to be relocated by linear probing, and how much probing was needed.

When you submit your code, the length of the longest cluster encountered when inserting a value as reported by your insert() function will be compared to the result from the reference code for correctness.
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <functional>

int insert(int value, std::vector<int> &table)
{
  // Code to insert value into a hashed location in table
  // where table is a vector of length 1000.
  // Returns the number of collisions encountered when
  // trying to insert value into table.
  int index = value % 1000;
  int count = 0;

  while (table[index] != -1)
  {
    index++;
    count++;
  }
  table[index] = value;

  return count;
}

int main()
{
  // Prepare some random but distinct values
  constexpr int NUM_VALUES = 500;
  std::vector<int> value(NUM_VALUES);
  int prev_value = 0;
  for (int i = 0; i < NUM_VALUES; i++)
  {
    prev_value += rand() % 25 + 1;
    value[i] = prev_value;
  }

  // Create hash table of size 1000 initialized with -1
  std::vector<int> table(1000, -1);

  // Insert values and track the maximum number of collisions
  int max_hit = 0, max_value = -1;
  for (int i = 0; i < NUM_VALUES; i++)
  {
    int hit = insert(value[i], table);
    if (hit > max_hit)
    {
      max_hit = hit;
      max_value = value[i];
    }
  }

  std::cout << "Inserting value " << max_value << " experienced " << max_hit << " collisions." << std::endl
            << std::endl;

  // Print the table contents
  for (int j = 0; j < 1000; j += 10)
  {
    std::cout << std::setw(3) << j << ":";
    for (int i = 0; i < 10; i++)
    {
      if (table[j + i] == -1)
        std::cout << "      ";
      else
        std::cout << std::setw(6) << table[j + i];
    }
    std::cout << std::endl;
  }

  return 0;
}

/*
Expected Output:

Inserting value 5326 experienced 4 collisions.

  0:        1001                          3006  6007  2008     9
 10:  4008  6010              3014  6014  1016  5016  5018  5019
 20:  4020    21  6018  6019    24  5025  6026  2027  4028      
 30:              3032        1034        5036                  
 40:    40                    1044              3047  2048  4049
 50:  6049                    5054        4056                59
 60:  1059  4061  5059  6063                                5069
 70:    70  2070  2072  3070  6073  6075              1078  1079
 80:  3078  4080    82        3084        6086        5088  3089
 90:              1092  4093  2094  5094  6096                  
100:   100  1101  2100  1103        2105  4106  1107            
110:        6111        3113              5116              2119
120:        1121                     125  3125              6129
130:  4130  1131              2134  1135  5134  1137  2138  5139
140:              1142              6145         147  3148  6148
150:              3152  4153  5153  2155  2156  6153  6158      
160:   160               163  4163  5165        1167            
170:  5170        5172  4173        1175  2175  2176  3177   179
180:              5182  6183        4185  1186  2186  1188   189
190:                                      3196  4196  6198      
200:        2201  5202   203         205  5205  1207  5208  6209
210:                          4214  5215  6214        3218      
220:         221  1222   223        5225  2226  4227            
230:                    6233  4234  1235  4236  1237  3237      
240:        2241              6244         246  5247  6247  1249
250:  4250  6248        3253  2254                     258      
260:        2261  6262              5265                    1269
270:   270              4273              3276                  
280:  2280                    1284  5284  6284        3288   289
290:  5288                          4295        2297        3299
300:  2300  4301        5303        1305  3305   307  3307  6309
310:               312                    2316              3319
320:   320  4321              6324  3325   326  1326  2326  3329
330:  5326                          3335  1336  5335  2338   339
340:  1340        6342        5344        2346  4346  2348      
350:                                      3356  6356  1358      
360:  1360  2361         363        2365  2366        3368  4368
370:  5368              4373  2374  6374                        
380:  5380   381        1383              1386        3388  4388
390:  3390  5389   392  5393        6395         397        2399
400:   400  4400              1404                              
410:                    3413  6414        4416  5417            
420:        2421  1422   423  5421  1425                    3429
430:  2430  5430   432  1432  1434  4434  6434        3438  5439
440:  1440  4440  6439        4444              4447  4448      
450:        2451   452  1452        3455  2456  6455  4458      
460:                    3463  5463  6463        4467        1469
470:   470  2469  3472                                      5479
480:  2480  6479              5484  1485              4488   489
490:                                       496  3497  6496  2499
500:  1500        5502                                 508      
510:  3510              4513              6516        2518  6518
520:  1520        2522  3523  5524         526  6526            
530:         531                          4536                  
540:  1540  2541        5543                          3548  3549
550:  5548  5549        2553         555  1556  2557  4556      
560:        1561  2562  3561  2564  3564              1568  2569
570:        5571                                 577  4578      
580:                                4585  1586  5585  2588  3589
590:        4591              3594  3595         597            
600:        4601  2602                           607  5608  1609
610:                          3614        2616              4619
620:   620                                                      
630:  2630  1631        5633              3636  2637  1638  1639
640:              4642         644                          1649
650:  5649        1652  2653  5653                    2658      
660:  3660        5662              4665  4666  3667  4667   669
670:  1670                    3674        5676  1677  2677  4678
680:  3680  2681                     685                    3689
690:                                2695                    5699
700:  1700  4701        5703  1704         706              3709
710:                                2715  1716                  
720:   720  3720   722  5721              4726                  
730:              1732  2733  3734  5733  5734  5737         739
740:  1739        4742               745              1748      
750:        2751   752                                      3759
760:  4760  5759  5760                    3766        1768      
770:                    2773  5774         776                  
780:              5782        4784              5787         789
790:        3791        1793                    1797  2798  4798
800:  5799                                                      
810:   810  5810        3813                    2817        1819
820:              4822  3823        5825        1827            
830:               832  1832              1836        2838   839
840:  4838                           845   846  2847  3847  5847
850:                                       856  1856  5858   859
860:        3861        2863  4863  5863        5867            
870:  5870   871  5871                           877  1877  4879
880:  3880                                            2888  4889
890:                                5895  1896  3896  4896   899
900:              5902         904  1905  5905                  
910:        2911  2912                    4916  3917   918  3919
920:        1921                    5925   926        4928      
930:              2932                    3936  1937  4936      
940:              4942                    3946        2948  5948
950:         951              2954                              
960:              1962  3962  4962              4967        2969
970:               972  4972  2974  5973              3978      
980:   980                    1984        2986        3988      
990:  3990        4992  5992                                    
*/

/*
Auto grader report:

We used your insert function to try inserting lots of distinct,
random values into several different tables. Results:
Your insert function reported 16 collisions in a case where we expected 16.
Your insert function reported 20 collisions in a case where we expected 20.
Your insert function reported 13 collisions in a case where we expected 13.

Correct!
*/