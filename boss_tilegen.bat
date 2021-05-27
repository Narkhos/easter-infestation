img2gb tileset --name boss_tileset --output-c-file=src/gfx/boss_tileset.c --output-header-file=src/gfx/boss_tileset.h --output-image=obj/gfx/boss.png --deduplicate img/boss.png

img2gb tilemap --name boss_idle_tilemap --output-c-file=src/gfx/boss_idle_tilemap.c --output-header-file=src/gfx/boss_idle_tilemap.h obj/gfx/boss.png img/boss_idle.png
img2gb tilemap --name boss_attack_tilemap --output-c-file=src/gfx/boss_attack_tilemap.c --output-header-file=src/gfx/boss_attack_tilemap.h obj/gfx/boss.png img/boss_attack.png