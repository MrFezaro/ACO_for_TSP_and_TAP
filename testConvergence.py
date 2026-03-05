import matplotlib.pyplot as plt

print("Paste convergence data, then press Enter twice:")
lines = []
while True:
    line = input()
    if line == "":
        break
    lines.append(line)

generations, distances = [], []
for line in lines:
    g, d = line.split()
    generations.append(int(g))
    distances.append(float(d))

is_tsp = max(distances) > 100

fig, ax = plt.subplots(figsize=(10, 5))
fig.patch.set_facecolor("#0d1b2a")
ax.set_facecolor("#0d1b2a")

ax.plot(generations, distances, color="#00aaff", linewidth=1.5, label="Best distance")

if is_tsp:
    ax.axhline(y=7115, color="#ff4444", linewidth=1, linestyle="--", label="Best known (7115)")

ax.set_title("ACO Convergence", fontsize=14, color="white", fontfamily="monospace")
ax.set_xlabel("Generation", color="#aaaaaa")
ax.set_ylabel("Best Distance" if is_tsp else "Best Cost", color="#aaaaaa")
ax.tick_params(colors="#555555")
ax.legend(facecolor="#0d1b2a", edgecolor="#2a4a6a", labelcolor="white")
ax.grid(True, linestyle="--", alpha=0.2, color="#aaaaaa")
for spine in ax.spines.values():
    spine.set_edgecolor("#1a3a5a")

plt.tight_layout()
plt.show()