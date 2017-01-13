# Simple Health example

from Viterbi import viterbi

states = ("Healthy", "Fever")  # States that can not be observed directly

# Observations, that long with the hidden states form a Hidden Markov
# Model (HMM)
observations = ("normal", "cold", "dizzy")

# Belief of which state the HMM is in during first visit
startProbability = {"Healthy": 0.6, "Fever": 0.4}


transitionProbability = {"Healthy": {"Healthy": 0.7, "Fever": 0.3},
                         "Fever": {"Healthy": 0.4, "Fever": 0.6}
                         }

# Change in health probability
emissionProbability = {"Healthy": {"normal": 0.5, "cold": 0.4, "dizzy": 0.1},
                       "Fever": {"normal": 0.1, "cold": 0.3, "dizzy": 0.6}
                       }


viterbi(observations, states, startProbability,
        transitionProbability, emissionProbability)
