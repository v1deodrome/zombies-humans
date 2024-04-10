# Zombies VS Humans

A simple predator/prey simulator featuring Zombies and Humans.

You can customize the ruleset in GameSpecs.h before compiling.

## Rules

### Zombies
Zombies operate in the following order:
- Kills them if they get too hungry (`ZOMBIE_STARVE`)
- Eat a human at an adjacent tile (resets hunger) or moves to an empty tile if none exist (increases hunger)
- If a zombie survives long enough, they'll turn an adjacent Human into a Zombie.

### Humans
Humans operate in the following order:
- Move to an adjacent tile and increment the birth counter
- If the birth counter is high enough (`HUMAN_BREED`), spawn another human at an adjacent tile.
