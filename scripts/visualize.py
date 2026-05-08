"""
Visualization script for simple-orbit-simulator simulation results.

This script reads the CSV output from the orbit simulator and generates
several plots to analyze the orbital mechanics and physics of the simulation.

Usage:
    python scripts/visualize.py build/simulation_result.csv
    python scripts/visualize.py build/simulation_result.csv --output ./plots
    python scripts/visualize.py build/simulation_result.csv --no-individual

Example:
    python scripts/visualize.py build/simulation_result.csv --output ./my_plots
"""

import argparse
import os
import sys

import matplotlib.pyplot as plt
import matplotlib.cm as cm
import numpy as np
import pandas as pd

from matplotlib.collections import LineCollection

# ---------------------------------------------------------------------------
# I/O helpers
# ---------------------------------------------------------------------------

def load_simulation_data(filepath: str) -> pd.DataFrame:
    """Load and validate simulation CSV data produced by the orbit simulator.

    The expected CSV format is semicolon-separated with a header row::

        Tick ; id ; x-pos ; y-pos ; mass

    Args:
        filepath: Path to the ``.csv`` file written by the simulator.

    Returns:
        A :class:`pandas.DataFrame` with columns ``tick``, ``id``,
        ``x``, ``y``, ``mass`` (all whitespace stripped from names).

    Raises:
        FileNotFoundError: If *filepath* does not exist.
        ValueError: If required columns are missing after parsing.
    """
    if not os.path.exists(filepath):
        raise FileNotFoundError(f"Simulation file not found: {filepath}")

    # Read raw text and strip trailing semicolons from each line,
    # then parse from the cleaned string buffer.
    with open(filepath, "r") as fh:
        raw = fh.read()

    cleaned_lines = [line.rstrip("; \t") for line in raw.splitlines()]
    cleaned = "\n".join(cleaned_lines)

    import io
    df = pd.read_csv(io.StringIO(cleaned), sep=";", skipinitialspace=True)

    # Normalise column names (strip whitespace, lower-case)
    df.columns = [c.strip().lower() for c in df.columns]

    # Drop unnamed / all-NaN columns produced by trailing delimiters
    df = df.loc[:, ~df.columns.str.startswith("unnamed")]
    df.dropna(how="all", axis=1, inplace=True)

    column_aliases = {
        "tick": "tick",
        "id": "id",
        "x-pos": "x",
        "y-pos": "y",
        "mass": "mass",
    }

    missing = [k for k in column_aliases if k not in df.columns]
    if missing:
        raise ValueError(
            f"CSV is missing required columns: {missing}. "
            f"Found columns: {list(df.columns)}"
        )

    df = df.rename(columns=column_aliases)
    df["tick"] = pd.to_numeric(df["tick"], errors="coerce")
    df["id"] = pd.to_numeric(df["id"], errors="coerce").astype(int)
    df["x"] = pd.to_numeric(df["x"], errors="coerce")
    df["y"] = pd.to_numeric(df["y"], errors="coerce")
    df["mass"] = pd.to_numeric(df["mass"], errors="coerce")
    df.dropna(inplace=True)

    return df


def ensure_output_dir(output_dir: str) -> None:
    """Create *output_dir* (and any parents) if it does not exist.

    Args:
        output_dir: Directory path to create.
    """
    os.makedirs(output_dir, exist_ok=True)


# ---------------------------------------------------------------------------
# Physics helpers
# ---------------------------------------------------------------------------

def compute_velocity(group: pd.DataFrame) -> pd.Series:
    """Compute the scalar velocity for each tick using finite differences.

    Velocity is approximated as ``sqrt(dx^2 + dy^2) / dt`` where *dt* is the
    difference between consecutive tick values.  The first entry is set to
    ``NaN`` because no previous position is available.

    Args:
        group: A :class:`pandas.DataFrame` slice for a **single** object,
            sorted ascending by ``tick``, containing columns ``x``, ``y``,
            and ``tick``.

    Returns:
        A :class:`pandas.Series` of scalar velocity values aligned to the
        index of *group*.
    """
    dx = group["x"].diff()
    dy = group["y"].diff()
    dt = group["tick"].diff().replace(0, np.nan)
    return np.sqrt(dx**2 + dy**2) / dt


def compute_altitude(group: pd.DataFrame, ref_x: float = 0.0, ref_y: float = 0.0) -> pd.Series:
    """Compute the distance of each position from a reference point.

    Args:
        group: A :class:`pandas.DataFrame` slice for a **single** object
            with columns ``x`` and ``y``.
        ref_x: X-coordinate of the reference point (default ``0.0``).
        ref_y: Y-coordinate of the reference point (default ``0.0``).

    Returns:
        A :class:`pandas.Series` of distances (same index as *group*).
    """
    return np.sqrt((group["x"] - ref_x)**2 + (group["y"] - ref_y)**2)


# ---------------------------------------------------------------------------
# Plot: system overview
# ---------------------------------------------------------------------------

def plot_system_overview(df: pd.DataFrame, output_dir: str) -> None:
    """Generate a single overview plot showing all object trajectories.

    Objects are distinguished by colour.  Marker size is proportional to
    the object's median mass (clamped to a sensible range).  Start and end
    positions are annotated.

    Args:
        df: Full simulation data as returned by :func:`load_simulation_data`.
        output_dir: Directory where the PNG file will be saved.
    """
    object_ids = sorted(df["id"].unique())
    colors = cm.tab10(np.linspace(0, 1, len(object_ids)))

    fig, ax = plt.subplots(figsize=(10, 10))
    ax.set_facecolor("#0d0d1a")
    fig.patch.set_facecolor("#0d0d1a")

    for obj_id, color in zip(object_ids, colors):
        obj_data = df[df["id"] == obj_id].sort_values("tick")

        ax.plot(
            obj_data["x"],
            obj_data["y"],
            color=color,
            linewidth=0.8,
            alpha=0.85,
            label=f"Object {obj_id}",
        )

        # Marker size proportional to mass
        median_mass = obj_data["mass"].median()
        marker_size = np.clip(np.log1p(median_mass) * 3, 4, 30)

        start = obj_data.iloc[0]
        end = obj_data.iloc[-1]

        ax.scatter(start["x"], start["y"], color=color, s=marker_size * 4,
                   marker="o", zorder=5, edgecolors="white", linewidths=0.5)
        ax.scatter(end["x"], end["y"], color=color, s=marker_size * 4,
                   marker="X", zorder=5, edgecolors="white", linewidths=0.5)

    ax.set_title("System Overview — All Trajectories", color="white", fontsize=14, pad=12)
    ax.set_xlabel("X Position", color="#aaaaaa")
    ax.set_ylabel("Y Position", color="#aaaaaa")
    ax.tick_params(colors="#aaaaaa")
    ax.grid(True, linestyle="--", alpha=0.2, color="white")
    for spine in ax.spines.values():
        spine.set_edgecolor("#333355")

    legend = ax.legend(facecolor="#1a1a2e", edgecolor="#333355", labelcolor="white",
                       loc="upper right", fontsize=9)

    plt.tight_layout()
    save_path = os.path.join(output_dir, "system_overview.png")
    plt.savefig(save_path, dpi=150, bbox_inches="tight", facecolor=fig.get_facecolor())
    plt.close(fig)
    print(f"  [saved] {save_path}")


# ---------------------------------------------------------------------------
# Plot: individual trajectories
# ---------------------------------------------------------------------------

def plot_individual_trajectories(df: pd.DataFrame, output_dir: str) -> None:
    """Generate one trajectory plot per object.

    Each plot shows the path of a single object colour-coded by simulation
    time (tick), with start/end markers.

    Args:
        df: Full simulation data as returned by :func:`load_simulation_data`.
        output_dir: Directory where PNG files will be saved.  Files are
            named ``trajectory_object_<id>.png``.
    """
    object_ids = sorted(df["id"].unique())

    for obj_id in object_ids:
        obj_data = df[df["id"] == obj_id].sort_values("tick")

        fig, ax = plt.subplots(figsize=(7, 7))
        ax.set_facecolor("#0d0d1a")
        fig.patch.set_facecolor("#0d0d1a")

        ticks = obj_data["tick"].values
        x = obj_data["x"].values
        y = obj_data["y"].values

        # Draw trajectory segments coloured by time
        points = np.array([x, y]).T.reshape(-1, 1, 2)
        segments = np.concatenate([points[:-1], points[1:]], axis=1)

        norm = plt.Normalize(ticks.min(), ticks.max())
        lc = LineCollection(segments, cmap="plasma", norm=norm, linewidth=1.2, alpha=0.9)
        lc.set_array(ticks[:-1])
        ax.add_collection(lc)

        cbar = fig.colorbar(lc, ax=ax, pad=0.02)
        cbar.set_label("Tick (time)", color="#aaaaaa")
        cbar.ax.yaxis.set_tick_params(color="#aaaaaa")
        plt.setp(cbar.ax.yaxis.get_ticklabels(), color="#aaaaaa")

        ax.scatter(x[0], y[0], color="lime", s=60, zorder=5,
                   marker="o", label="Start", edgecolors="white", linewidths=0.5)
        ax.scatter(x[-1], y[-1], color="red", s=60, zorder=5,
                   marker="X", label="End", edgecolors="white", linewidths=0.5)

        ax.autoscale()
        ax.set_title(f"Trajectory — Object {obj_id}", color="white", fontsize=13, pad=10)
        ax.set_xlabel("X Position", color="#aaaaaa")
        ax.set_ylabel("Y Position", color="#aaaaaa")
        ax.tick_params(colors="#aaaaaa")
        ax.grid(True, linestyle="--", alpha=0.15, color="white")
        for spine in ax.spines.values():
            spine.set_edgecolor("#333355")

        ax.legend(facecolor="#1a1a2e", edgecolor="#333355", labelcolor="white", fontsize=9)

        plt.tight_layout()
        save_path = os.path.join(output_dir, f"trajectory_object_{obj_id}.png")
        plt.savefig(save_path, dpi=150, bbox_inches="tight", facecolor=fig.get_facecolor())
        plt.close(fig)
        print(f"  [saved] {save_path}")


# ---------------------------------------------------------------------------
# Plot: velocity vs time
# ---------------------------------------------------------------------------

def plot_velocity_time(df: pd.DataFrame, output_dir: str) -> None:
    """Plot scalar velocity over time for every object on a single figure.

    Velocity is derived from finite differences of position data (see
    :func:`compute_velocity`).

    Args:
        df: Full simulation data as returned by :func:`load_simulation_data`.
        output_dir: Directory where the PNG file will be saved.
    """
    object_ids = sorted(df["id"].unique())
    colors = cm.tab10(np.linspace(0, 1, len(object_ids)))

    fig, ax = plt.subplots(figsize=(11, 5))
    ax.set_facecolor("#0d0d1a")
    fig.patch.set_facecolor("#0d0d1a")

    for obj_id, color in zip(object_ids, colors):
        obj_data = df[df["id"] == obj_id].sort_values("tick").copy()
        obj_data["velocity"] = compute_velocity(obj_data)

        ax.plot(
            obj_data["tick"],
            obj_data["velocity"],
            color=color,
            linewidth=1.0,
            alpha=0.85,
            label=f"Object {obj_id}",
        )

    ax.set_title("Velocity vs Time", color="white", fontsize=14, pad=10)
    ax.set_xlabel("Tick", color="#aaaaaa")
    ax.set_ylabel("Velocity (units/tick)", color="#aaaaaa")
    ax.tick_params(colors="#aaaaaa")
    ax.grid(True, linestyle="--", alpha=0.2, color="white")
    for spine in ax.spines.values():
        spine.set_edgecolor("#333355")

    ax.legend(facecolor="#1a1a2e", edgecolor="#333355", labelcolor="white", fontsize=9)

    plt.tight_layout()
    save_path = os.path.join(output_dir, "velocity_time.png")
    plt.savefig(save_path, dpi=150, bbox_inches="tight", facecolor=fig.get_facecolor())
    plt.close(fig)
    print(f"  [saved] {save_path}")


# ---------------------------------------------------------------------------
# Plot: altitude vs time
# ---------------------------------------------------------------------------

def plot_altitude_time(df: pd.DataFrame, output_dir: str) -> None:
    """Plot distance from the coordinate origin over time for every object.

    The "altitude" here is simply the Euclidean distance from ``(0, 0)``,
    which serves as a proxy for orbital radius / distance from the system
    barycentre.

    Args:
        df: Full simulation data as returned by :func:`load_simulation_data`.
        output_dir: Directory where the PNG file will be saved.
    """
    object_ids = sorted(df["id"].unique())
    colors = cm.tab10(np.linspace(0, 1, len(object_ids)))

    fig, ax = plt.subplots(figsize=(11, 5))
    ax.set_facecolor("#0d0d1a")
    fig.patch.set_facecolor("#0d0d1a")

    for obj_id, color in zip(object_ids, colors):
        obj_data = df[df["id"] == obj_id].sort_values("tick").copy()
        obj_data["altitude"] = compute_altitude(obj_data)

        ax.plot(
            obj_data["tick"],
            obj_data["altitude"],
            color=color,
            linewidth=1.0,
            alpha=0.85,
            label=f"Object {obj_id}",
        )

    ax.set_title("Altitude (Distance from Origin) vs Time", color="white", fontsize=14, pad=10)
    ax.set_xlabel("Tick", color="#aaaaaa")
    ax.set_ylabel("Distance from Origin", color="#aaaaaa")
    ax.tick_params(colors="#aaaaaa")
    ax.grid(True, linestyle="--", alpha=0.2, color="white")
    for spine in ax.spines.values():
        spine.set_edgecolor("#333355")

    ax.legend(facecolor="#1a1a2e", edgecolor="#333355", labelcolor="white", fontsize=9)

    plt.tight_layout()
    save_path = os.path.join(output_dir, "altitude_time.png")
    plt.savefig(save_path, dpi=150, bbox_inches="tight", facecolor=fig.get_facecolor())
    plt.close(fig)
    print(f"  [saved] {save_path}")


# ---------------------------------------------------------------------------
# CLI entry-point
# ---------------------------------------------------------------------------

def parse_args() -> argparse.Namespace:
    """Parse command-line arguments.

    Returns:
        Parsed :class:`argparse.Namespace` object.
    """
    parser = argparse.ArgumentParser(
        description="Visualize orbit simulator CSV output.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__,
    )
    parser.add_argument(
        "csv_file",
        help="Path to the simulation result CSV file.",
    )
    parser.add_argument(
        "--output",
        default="plots",
        metavar="DIR",
        help="Directory to save generated plots (default: ./plots).",
    )
    parser.add_argument(
        "--no-individual",
        action="store_true",
        help="Skip individual per-object trajectory plots.",
    )
    return parser.parse_args()


def main() -> None:
    """Entry point: load data and generate all visualizations."""
    args = parse_args()

    print(f"Loading data from: {args.csv_file}")
    df = load_simulation_data(args.csv_file)

    if df.empty:
        print("Error: No data loaded. Exiting.")
        sys.exit(1)

    object_ids = sorted(df["id"].unique())
    ticks = df["tick"].nunique()
    print(f"  Objects: {object_ids}")
    print(f"  Ticks:   {ticks}")

    ensure_output_dir(args.output)
    print(f"Saving plots to: {args.output}/\n")

    print("Generating system overview...")
    plot_system_overview(df, args.output)

    if not args.no_individual:
        print("Generating individual trajectories...")
        plot_individual_trajectories(df, args.output)

    print("Generating velocity/time graph...")
    plot_velocity_time(df, args.output)

    print("Generating altitude/time graph...")
    plot_altitude_time(df, args.output)

    print("\nDone! All plots saved.")


if __name__ == "__main__":
    main()
