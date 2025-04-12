import numpy as np
from SMPyBandits.Environment import Evaluator, tqdm
from SMPyBandits.Arms import Bernoulli
from SMPyBandits.Policies.BasePolicy import BasePolicy
from math import pow

# Define diminishing Epsilon-Greedy class
class DiminishingEpsilonGreedy(BasePolicy):
    """Epsilon-Greedy policy with diminishing exploration rate (epsilon(t) = t^(-alpha))."""

    def __init__(self, nbArms, alpha=0.1, lower=0.0, amplitude=1.0):
        super(DiminishingEpsilonGreedy, self).__init__(nbArms, lower=lower, amplitude=amplitude)
        assert alpha > 0, "Error: 'alpha' for diminishing epsilon must be positive."
        self._alpha = alpha
        self._t = 1  # Initialize time step

    def choice(self):
        """With a diminishing probability of exploration, explore or exploit."""
        epsilon_t = pow(self._t, -self._alpha)  # Calculate diminishing epsilon
        self._t += 1  # Increment time step
        if np.random.random() < epsilon_t:
            # Exploration: Choose a random arm
            return np.random.randint(self.nbArms)
        else:
            # Exploitation: Choose the best arm based on empirical rewards
            return np.argmax(self.rewards)

# Configuration for MAB environment
ENVIRONMENTS = [
    {"arm_type": Bernoulli, "params": [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]},
    {"arm_type": Bernoulli, "params": [0.01, 0.02, 0.3, 0.4, 0.5, 0.6, 0.795, 0.8, 0.805]},
    {"arm_type": Bernoulli, "params": [0.01, 0.01, 0.01, 0.02, 0.02, 0.02, 0.05, 0.05, 0.1]},
]

# Parameters for policies
ALPHA_VALUES = [0.1, 0.5, 1.0, 2.0]
POLICIES = [
    {"archtype": DiminishingEpsilonGreedy, "params": {"alpha": alpha}} for alpha in ALPHA_VALUES
]

# Configuration for experiment
configuration = {
    "horizon": 10000,
    "repetitions": 100,
    "n_jobs": 1,
    "verbosity": 6,
    "environment": ENVIRONMENTS,
    "policies": POLICIES,
}

# Create Evaluator and run experiments
evaluation = Evaluator(configuration)

# Run evaluation for all environments
for envId, env in tqdm(enumerate(evaluation.envs), desc="Problems"):
    evaluation.startOneEnv(envId, env)

# Function to display and plot results for all environments
def plotAllResults(evaluation):
    for envId in range(len(evaluation.envs)):
        print(f"\nResults for Environment {envId + 1}:")
        evaluation.printFinalRanking(envId)
        evaluation.plotRegrets(envId)

# Plot all results
plotAllResults(evaluation)
