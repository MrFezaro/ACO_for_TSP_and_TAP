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
    g, d = map(int, line.split())
    generations.append(g)
    distances.append(d)

fig, ax = plt.subplots(figsize=(10, 5))

ax.plot(generations, distances, color="#0055cc", linewidth=1.5, label="Best distance")
ax.axhline(y=7115, color="#cc0000", linewidth=1, linestyle="--", label="Best known (7115)")

ax.set_title("ACO Convergence", fontsize=14)
ax.set_xlabel("Generation")
ax.set_ylabel("Best Distance")
ax.legend()
ax.grid(True, linestyle="--", alpha=0.4)

plt.tight_layout()
plt.show()