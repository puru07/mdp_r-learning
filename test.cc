#include "mdp-simulation.h"
#include <iostream>
using namespace std;

int main (void)
{
  State nextState = my_next_state(State(0, 0), N);
  cout << "From 0, 0 to " << nextState.x << ", " << nextState.y << endl;
  nextState = my_next_state(State(nextState.x, nextState.y), N);
  cout << "From 0, 0 to " << nextState.x << ", " << nextState.y << endl;
  Reward reward = my_reward(State(1, 1));
  cout << "Receiving reward " << reward << endl;
  return 0;
}
