import numpy as np

# Monte Carlo Simulation for estimating Euler's number e
def estimate_e(num_trials):
    estimates = []
    for _ in range(num_trials):
        running_sum = 0
        n = 0
        # Generate uniform random variables and calculate the running sum
        while running_sum <= 1:
            running_sum += np.random.uniform(0, 1)
            n += 1
        estimates.append(n)
    # Return the average of trials as the estimate for e
    return np.mean(estimates)

# Main execution for different numbers of trials
trial_counts = [10**1, 10**3, 10**5, 10**7]
results = {}

print("Monte Carlo Estimation of Euler's Number e:")
for count in trial_counts:
    e_estimate = estimate_e(count)
    results[count] = e_estimate
    print(f"Number of trials: {count}, Estimated e: {e_estimate:.5f}")
