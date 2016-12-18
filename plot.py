import csv
import matplotlib.pyplot as plt

reward = []
with open('op_reward.txt') as csvfile:
	csv0 = csv.reader(csvfile, delimiter=',')
	for row in csv0:
		reward = row
print reward[1:10]
# print type(reward[0])
# for i in range(len(reward)):
# 	reward[i] = int(reward[i])
reward.reverse()
plt.plot(reward,'ro')
plt.xlabel('Episode')
plt.ylabel('Reward')
plt.show()