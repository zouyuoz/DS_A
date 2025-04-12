import random
import matplotlib.pyplot as plt

class Bandit:
    def __init__(self, prob):
        self.prob = prob
        self.score = 0
        self.tried = 0

    def play(self):
        self.tried += 1
        if random.random() < self.prob:
            self.score += 1
            return 1
        return 0

    def spec_prob(self):
        if self.tried == 0:
            return 0.0
        return self.score / self.tried

def bandits(case_num):
    cases = [
        [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9],
        [0.01, 0.02, 0.3, 0.4, 0.5, 0.6, 0.795, 0.8, 0.805],
        [0.01, 0.01, 0.01, 0.02, 0.02, 0.02, 0.05, 0.05, 0.1],
    ]
    return [Bandit(prob) for prob in cases[case_num]]

def find_best_bandit(bandits_list):
    best_bandit = 0
    best_score = 0.0
    for i, b in enumerate(bandits_list):
        if b.spec_prob() > best_score:
            best_bandit = i
            best_score = b.spec_prob()
    # 若無 bandit 嘗試過或表現都很差，隨機挑一個
    if best_score < 0.001:
        return random.randint(0, len(bandits_list)-1)
    return best_bandit

def run_bandit(players_epsilons, case_number, time):
    num_players = len(players_epsilons)
    # 每個玩家有自己獨立的 bandit 集合
    all_players_bandits = [bandits(case_number) for _ in range(num_players)]

    player_scores = [[] for _ in range(num_players)]  
    player_totals = [0] * num_players  

    # 初始化每位玩家的最佳 bandit 選擇
    best_bandits = [random.randint(0, len(all_players_bandits[0]) - 1) for _ in range(num_players)]

    for t in range(1, time + 1):
        for p in range(num_players):
            epsilon = players_epsilons[p]  # 若想衰退，可換成 pow(t, players_epsilons[p])
            # epsilon = pow(t, players_epsilons[p])

            # epsilon-greedy 選擇
            if random.random() < epsilon:
                chosen_bandit = random.randint(0, len(all_players_bandits[p]) - 1)
            else:
                # 使用當前最佳評估
                chosen_bandit = best_bandits[p]

            reward = all_players_bandits[p][chosen_bandit].play()
            player_totals[p] += reward

            # 更新最佳 bandit
            best_bandits[p] = find_best_bandit(all_players_bandits[p])

        # 每100次記錄一次
        if t % 100 == 0:
            for p in range(num_players):
                # player_scores[p].append(player_totals[p] / t)
                player_scores[p].append(best_bandits[p])

    return player_scores

def main(case_number, time, players_epsilons):
    player_scores = run_bandit(players_epsilons, case_number, time)
    x = range(100, time + 1, 100)
    for p, scores in enumerate(player_scores):
        plt.plot(x, scores, label=f"Player {p} (epsilon: {players_epsilons[p]})")

    plt.xlabel("Iterations")
    plt.ylabel("Total Scores")
    plt.title("Multi-Player Bandit Simulation (Independent Sets)")
    plt.legend()
    plt.show()

if __name__ == "__main__":
    players_epsilons = [0.01, 0.03, 0.1, 0.3]
    # players_epsilons = [-0.1, -0.5, -1, -2]
    case_number = 1
    time = 10000
    main(case_number, time, players_epsilons)
