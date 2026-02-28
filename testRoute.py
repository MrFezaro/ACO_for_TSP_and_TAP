import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np

route = list(map(int, input("Enter route: ").split()))

cities = [
    ("Oslo",          59.91, 10.75),
    ("Bergen",        60.39,  5.27),
    ("Trondheim",     63.39, 10.40),
    ("Stavanger",     58.46,  6.43),
    ("Bærum",         59.95, 10.54),
    ("Kristiansand",  58.72,  9.44),
    ("Fredrikstad",   59.21, 11.08),
    ("Tromsø",        69.84, 18.74),
    ("Drammen",       59.73, 10.04),
    ("Sandnes",       58.86,  6.59),
    ("Sarpsborg",     59.21, 11.00),
    ("Bodø",          68.29, 15.12),
    ("Sandefjord",    59.21, 10.73),
    ("Ålesund",       62.86,  9.52),
    ("Tønsberg",      59.19, 10.73),
    ("Skien",         59.03, 10.59),
    ("Moss",          59.27, 10.75),
    ("Haugesund",     59.85,  6.12),  # index 17 - fixed from 5985->59.85
    ("Arendal",       58.78,  9.64),
    ("Hamar",         60.69, 11.08),
    ("Larvik",        59.04, 10.09),
    ("Halden",        59.12, 11.48),
    ("Lillehammer",   60.61, 11.31),
    ("Molde",         62.60,  7.43),
    ("Horten",        59.41, 10.32),
    ("Harstad",       68.61, 16.62),
    ("Gjøvik",        60.73, 10.38),
    ("Kristiansund",  63.10,  7.98),
    ("Narvik",        68.42, 17.48),
    ("Steinkjer",     64.21, 11.08),
    ("Levanger",      63.58, 11.13),
    ("Porsgrunn",     59.88,  9.59),
    ("Alta",          69.97, 23.30),
    ("Mo i Rana",     66.32, 14.22),
    ("Elverum",       60.87, 11.30),
    ("Namsos",        64.45, 11.56),
    ("Kongsvinger",   60.20, 12.01),
    ("Mosjøen",       65.83, 13.17),
    ("Verdal",        63.39, 11.25),
    ("Røros",         62.57, 11.63),
    ("Svolvær",       68.25, 14.83),
    ("Grimstad",      58.27,  8.26),
    ("Florø",         61.60,  4.95),
    ("Førde",         61.88,  5.72),
    ("Sogndal",       61.24,  7.64),
    ("Sunndalsøra",   62.22,  8.64),
    ("Hammerfest",    70.40, 23.63),
    ("Vardø",         70.37, 31.05),
    ("Kirkenes",      69.42, 30.05),
    ("Vadsø",         70.06, 29.40),
]

fig, ax = plt.subplots(figsize=(10, 16))
fig.patch.set_facecolor("#0d1b2a")
ax.set_facecolor("#0d1b2a")

# Plot all cities as dim dots
for name, lat, lon in cities:
    ax.plot(lon, lat, 'o', color="#2a4a6a", markersize=4, zorder=2)

# Draw route edges with gradient color
n = len(route) - 1
cmap = plt.cm.plasma
for i in range(n):
    c1 = cities[route[i]]
    c2 = cities[route[i+1]]
    color = cmap(i / n)
    ax.annotate("", xy=(c2[2], c2[1]), xytext=(c1[2], c1[1]),
                arrowprops=dict(arrowstyle="-|>", color=color, lw=1.8))

# Highlight route cities
for idx, city_idx in enumerate(route[:-1]):
    name, lat, lon = cities[city_idx]
    color = cmap(idx / n)
    ax.plot(lon, lat, 'o', color=color, markersize=8, zorder=4,
            markeredgecolor="white", markeredgewidth=0.5)
    ax.text(lon + 0.15, lat, name, color=color, fontsize=7,
            fontfamily="monospace", zorder=5)

# Start city marker
start = cities[route[0]]
ax.plot(start[2], start[1], '*', color="#ffdd00", markersize=16, zorder=6,
        markeredgecolor="white", markeredgewidth=0.8)

ax.set_title("TSP Route — Norway", color="white",
             fontsize=16, fontfamily="monospace", pad=16)
ax.set_xlabel("Longitude", color="#aaaaaa", fontsize=9)
ax.set_ylabel("Latitude", color="#aaaaaa", fontsize=9)
ax.tick_params(colors="#555555")
for spine in ax.spines.values():
    spine.set_edgecolor("#1a3a5a")

star = mpatches.Patch(color="#ffdd00", label="StarAt city")
ax.legend(handles=[star], facecolor="#0d1b2a", edgecolor="#2a4a6a",
          labelcolor="white", fontsize=9, loc="lower right")

plt.tight_layout()
plt.show()