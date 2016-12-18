#include "mdp-simulation.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

int main (int argc,char** argv)
{
  // State nextState = my_next_state(State(0, 0), N);
  // cout << "From 0, 0 to " << nextState.x << ", " << nextState.y << endl;
  // Reward reward = my_reward(State(1, 1));
  // cout << "Receiving reward " << reward << endl;
	int max_episodes = 1000000;
	int niter = 100;
	float eps = 1.0;
	float epsdel = eps/max_episodes;
	eps = eps + epsdel;
	Action act[] = {N, S, E, W};		//actions
	//cout<<"actions are  "<<act[0]<<" "<<act[1]<<" "<<act[2]<<" "<<act[3]<<endl;
	float lrate = 0.5;						// learning rate: alpha
	float gamma = 0.9;						// discount
	int max_grid = MAX_GRID;
	cout<<"max grid size "<<max_grid<<endl;
	int nstate ;
	float fqval ;
	int iact;
	int reward = 0;
	int currx, curry = 0;
	float toss;
	State nextState;

	Reward curr_reward, max_reward;
	std::vector<Reward> ep_reward;
	vector< vector<float> > qval; 
	vector<Action>  policy;
	
	
	for (int i = 0;i<max_grid*max_grid;i++)
	{
		vector<float> row;
		for (int j = 0; j< 4;j++)
		{
			row.push_back(float(0));
		}
		qval.push_back(row);
	}
	for(int episodes = 0; episodes < max_episodes;episodes++)
	{

		ep_reward.push_back(0);
		eps = eps - epsdel;
		//cout<<"--------> episode number "<<episodes<<endl;
		currx = rand() % max_grid;
		curry = rand() % max_grid;
		for (int iter = 0;iter < niter;iter ++)
		{
			//exploit exl = 1 or explore exp = 0
			toss =  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			//cout<<"toss value "<<toss<<endl;
			int exl = 0;
			if (toss >eps)
			{
				exl = 1 ;	// exploit

				//cout<<"exploit "<<endl;
			}
			else 
			{
				exl = 0;

			}

			if (exl == 0)		//explore
			{
				//chossing the action randomly
				iact = rand()% 4;
				//cout<<"taking the action "<<act[iact]<<endl;
				curr_reward = my_reward(State(currx, curry));
				nextState = my_next_state(State(currx, curry), act[iact]);
				
				currx = nextState.x; curry = nextState.y;

				nstate = max_grid*nextState.x + nextState.y;
				fqval = *max_element(qval[nstate].begin(),qval[nstate].end());
				
				qval[nstate][iact] = (1-lrate)*qval[nstate][iact] + lrate*(curr_reward + gamma*fqval);
				
				
				ep_reward[episodes] += curr_reward; 
			}
			if (exl ==1)		//exploit
			{
				curr_reward = my_reward(State(currx, curry));
				nstate = max_grid*nextState.x + nextState.y;
				iact = max_element(qval[nstate].begin(),qval[nstate].end() ) - qval[nstate].begin();
				//cout<<"taking the action "<<act[iact]<<endl;
				nextState = my_next_state(State(currx, curry), act[iact]);

				currx = nextState.x; curry = nextState.y;

				nstate = 10*nextState.x + nextState.y;
				fqval = *max_element(qval[nstate].begin(),qval[nstate].end());
				qval[nstate][iact] = (1-lrate)*qval[nstate][iact] + lrate*(curr_reward + gamma*fqval);
				
				//curr_reward = my_reward(State(nextState.x, nextState.y));
				ep_reward[episodes] += curr_reward; 
			}
			


		}
		//cout<< "reward of this episode is "<<ep_reward[episodes]<<endl;
	}
	// finding the policy

	for(int nstate = 0; nstate< max_grid*max_grid;nstate++)
	{
		iact = max_element(qval[nstate].begin(),qval[nstate].end() ) - qval[nstate].begin();
		policy.push_back(act[iact]); 
		//cout<<"policy for state "<<nstate<<" "<<act[iact]<<endl; 
	}
	//writing the rewards to a file
	max_reward = *max_element(ep_reward.begin(),ep_reward.end());
	cout<< "maximum reward attained is "<<max_reward<<endl;
	ofstream reward_file;
	reward_file.open("op_reward.txt");
	for(int i = 0;i<max_episodes;i++)
	{
		reward_file<<ep_reward[i]<<",";
	}
	reward_file.close();

	//writing the policy
	ofstream policy_file;
	policy_file.open("policy.txt");
	policy_file<<"the x and y coordinate of the state, followed by thier respective action"<<endl;
	for(int y = 0; y< max_grid;y++)
	{
		
		for(int x= 0; x< max_grid;x++)
		{
			nstate = max_grid*x+y;
			if (policy[nstate] == 0)
			{
				policy_file<<"N,";
			}
			else if (policy[nstate] ==1)
			{
				policy_file<<"S,";
			}
			else if (policy[nstate] ==2)
			{
				policy_file<<"E,";
			}
			else 
			{
				policy_file<<"W,";
			}
		}
		policy_file<<"\n";

	}
	policy_file.close();
	
	return 0;
}
