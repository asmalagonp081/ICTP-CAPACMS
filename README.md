# Comparative Analysis of Photon Attenuation Coefficients in Multilayer Shielding using Geant4 and MULASSIS

## Abstract 🌷

The interaction of ionizing radiation with matter is a critical factor in the design of biological shielding. This work develops a radiation-matter interaction simulation using the Monte Carlo method, specifically employing the Geant4 toolkit to model and calculate the attenuation coefficients of a photon beam within the 10^{-1} to 10^{1} MeV energy range for two multilayer material configurations: lead-concrete and polyethylene-aluminum.

Rather than recording energy deposition, the implementation focuses on particle fluence by utilizing scoring planes positioned at the material interfaces. This approach enables the determination of the transmission factor and the Half-Value Layer (HVL) for each configuration. Data processing and statistical analysis are performed in Python using the Pandas library. Finally, the results are benchmarked against the European Space Agency’s (ESA) MULASSIS tool, allowing for a comparison of the attenuation coefficients obtained in composite material configurations for photons across this energy spectrum.