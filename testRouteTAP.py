import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

taxis = [
    ("Aalesund Station",        62.4722, 6.1495),
    ("Brosundet Quay",          62.4706, 6.1512),
    ("Aalesund Hospital",       62.4780, 6.1620),
    ("Moa Shopping Centre",     62.4782, 6.2301),
    ("Borgundvegen Stand",      62.4745, 6.1890),
    ("Aspoy Ferry Terminal",    62.4658, 6.1423),
    ("Hessa Beach",             62.4601, 6.0987),
    ("Nurvasund Bridge",        62.4831, 6.1723),
    ("Aalesund Airport Vigra",  62.5600, 6.1197),
    ("Skarbovik Harbour",       62.4689, 6.1834),
]

customers = [
    ("Hotel Brosundet",         62.4710, 6.1530),
    ("Jugendstilsenteret",      62.4718, 6.1487),
    ("Aksla Viewpoint",         62.4739, 6.1552),
    ("Atlantic Sea Park",       62.4648, 6.0921),
    ("Aalesund University",     62.4716, 6.2028),
    ("Storfjord Hotel",         62.4923, 6.9823),
    ("Molovegen Pier",          62.4695, 6.1468),
    ("Buholmen Island",         62.4672, 6.1389),
    ("Storgata Shopping",       62.4727, 6.1512),
    ("Roysa Residential",       62.4850, 6.1901),
]

print("Paste assignment output lines, then press Enter twice:")
lines = []
while True:
    line = input()
    if line == "":
        break
    lines.append(line)

assignments = []
for line in lines:
    if "->" not in line:
        continue
    left, right = line.split("->")
    taxi_name = left.replace("Taxi", "").strip()
    customer_name = right.replace("Customer", "").split("(")[0].strip()
    taxi = next((t for t in taxis if t[0] == taxi_name), None)
    customer = next((c for c in customers if c[0] == customer_name), None)
    if taxi and customer:
        assignments.append((taxi, customer))

print(f"Matched {len(assignments)} assignments")

fig, ax = plt.subplots(figsize=(12, 8))
fig.patch.set_facecolor("#0d1b2a")
ax.set_facecolor("#0d1b2a")

cmap = plt.cm.tab10
for i, (taxi, customer) in enumerate(assignments):
    color = cmap(i / max(len(assignments), 1))
    ax.annotate("", xy=(customer[2], customer[1]), xytext=(taxi[2], taxi[1]),
                arrowprops=dict(arrowstyle="-|>", color=color, lw=1.8))

for name, lat, lon in taxis:
    ax.plot(lon, lat, 's', color="#00aaff", markersize=10, zorder=4,
            markeredgecolor="white", markeredgewidth=0.8)
    ax.text(lon + 0.001, lat, name, fontsize=7, color="#00aaff")

for name, lat, lon in customers:
    ax.plot(lon, lat, 'o', color="#ff6655", markersize=10, zorder=4,
            markeredgecolor="white", markeredgewidth=0.8)
    ax.text(lon + 0.001, lat, name, fontsize=7, color="#ff6655")

taxi_patch = mpatches.Patch(color="#00aaff", label="Taxi stand")
customer_patch = mpatches.Patch(color="#ff6655", label="Customer")
ax.legend(handles=[taxi_patch, customer_patch], fontsize=9,
          facecolor="#0d1b2a", edgecolor="#2a4a6a", labelcolor="white")

ax.set_title("TAP - Taxi Assignment, Aalesund", fontsize=14, color="white", fontfamily="monospace")
ax.set_xlabel("Longitude", color="#aaaaaa")
ax.set_ylabel("Latitude", color="#aaaaaa")
ax.tick_params(colors="#555555")
ax.grid(True, linestyle="--", alpha=0.2, color="#aaaaaa")
for spine in ax.spines.values():
    spine.set_edgecolor("#1a3a5a")

plt.tight_layout()
plt.show()