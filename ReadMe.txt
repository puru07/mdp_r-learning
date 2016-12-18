the main file is q3.cpp
to run it
g++ -o q3 q3.cpp -l mdp-simulation -L.
./q3

it will give two outpus:
op_policy.txt 		: contains the policy
op_reward.txt		: contains the reward
policy.txt 			: contains policy in another format

apologies for not providing a function to query.
however you can query from op_policy.txt.

further,
in q3.cpp
	vector< vector<float> > qval; 
	vector<Action>  policy;
conatins Q values and policy respectively.

