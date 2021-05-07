img2gb tileset --name dungeon_tileset --output-c-file=src/gfx/dungeon_tileset.c --output-header-file=src/gfx/dungeon_tileset.h --output-image=obj/gfx/dungeon.png --deduplicate img/dungeon.png

img2gb tilemap --name bg_tilemap --output-c-file=src/gfx/bg_tilemap.c --output-header-file=src/gfx/bg_tilemap.h obj/gfx/dungeon.png img/bg.png
img2gb tilemap --name center_far_tilemap --output-c-file=src/gfx/center_far_tilemap.c --output-header-file=src/gfx/center_far_tilemap.h obj/gfx/dungeon.png img/center_far.png
img2gb tilemap --name center_near_tilemap --output-c-file=src/gfx/center_near_tilemap.c --output-header-file=src/gfx/center_near_tilemap.h obj/gfx/dungeon.png img/center_near.png
img2gb tilemap --name left_far_front_tilemap --output-c-file=src/gfx/left_far_front_tilemap.c --output-header-file=src/gfx/left_far_front_tilemap.h obj/gfx/dungeon.png img/left_far_front.png
img2gb tilemap --name left_far_side_tilemap --output-c-file=src/gfx/left_far_side_tilemap.c --output-header-file=src/gfx/left_far_side_tilemap.h obj/gfx/dungeon.png img/left_far_side.png
img2gb tilemap --name left_near_front_tilemap --output-c-file=src/gfx/left_near_front_tilemap.c --output-header-file=src/gfx/left_near_front_tilemap.h obj/gfx/dungeon.png img/left_near_front.png
img2gb tilemap --name left_near_side_tilemap --output-c-file=src/gfx/left_near_side_tilemap.c --output-header-file=src/gfx/left_near_side_tilemap.h obj/gfx/dungeon.png img/left_near_side.png
img2gb tilemap --name left_side_tilemap --output-c-file=src/gfx/left_side_tilemap.c --output-header-file=src/gfx/left_side_tilemap.h obj/gfx/dungeon.png img/left_side.png
img2gb tilemap --name right_far_front_tilemap --output-c-file=src/gfx/right_far_front_tilemap.c --output-header-file=src/gfx/right_far_front_tilemap.h obj/gfx/dungeon.png img/right_far_front.png
img2gb tilemap --name right_far_side_tilemap --output-c-file=src/gfx/right_far_side_tilemap.c --output-header-file=src/gfx/right_far_side_tilemap.h obj/gfx/dungeon.png img/right_far_side.png
img2gb tilemap --name right_near_front_tilemap --output-c-file=src/gfx/right_near_front_tilemap.c --output-header-file=src/gfx/right_near_front_tilemap.h obj/gfx/dungeon.png img/right_near_front.png
img2gb tilemap --name right_near_side_tilemap --output-c-file=src/gfx/right_near_side_tilemap.c --output-header-file=src/gfx/right_near_side_tilemap.h obj/gfx/dungeon.png img/right_near_side.png
img2gb tilemap --name right_side_tilemap --output-c-file=src/gfx/right_side_tilemap.c --output-header-file=src/gfx/right_side_tilemap.h obj/gfx/dungeon.png img/right_side.png

img2gb tilemap --name door_left_far_side_tilemap --output-c-file=src/gfx/door_left_far_side_tilemap.c --output-header-file=src/gfx/door_left_far_side_tilemap.h obj/gfx/dungeon.png img/door_left_far_side.png
img2gb tilemap --name door_right_far_side_tilemap --output-c-file=src/gfx/door_right_far_side_tilemap.c --output-header-file=src/gfx/door_right_far_side_tilemap.h obj/gfx/dungeon.png img/door_right_far_side.png

img2gb tilemap --name door_left_near_side_tilemap --output-c-file=src/gfx/door_left_near_side_tilemap.c --output-header-file=src/gfx/door_left_near_side_tilemap.h obj/gfx/dungeon.png img/door_left_near_side.png
img2gb tilemap --name door_right_near_side_tilemap --output-c-file=src/gfx/door_right_near_side_tilemap.c --output-header-file=src/gfx/door_right_near_side_tilemap.h obj/gfx/dungeon.png img/door_right_near_side.png

img2gb tilemap --name door_closed_left_side_tilemap --output-c-file=src/gfx/door_closed_left_side_tilemap.c --output-header-file=src/gfx/door_closed_left_side_tilemap.h obj/gfx/dungeon.png img/door_closed_left_side.png
img2gb tilemap --name door_closed_right_side_tilemap --output-c-file=src/gfx/door_closed_right_side_tilemap.c --output-header-file=src/gfx/door_closed_right_side_tilemap.h obj/gfx/dungeon.png img/door_closed_right_side.png

img2gb tilemap --name door_opened_left_side_tilemap --output-c-file=src/gfx/door_opened_left_side_tilemap.c --output-header-file=src/gfx/door_opened_left_side_tilemap.h obj/gfx/dungeon.png img/door_opened_left_side.png
img2gb tilemap --name door_opened_right_side_tilemap --output-c-file=src/gfx/door_opened_right_side_tilemap.c --output-header-file=src/gfx/door_opened_right_side_tilemap.h obj/gfx/dungeon.png img/door_opened_right_side.png

img2gb tilemap --name door_opened_near_tilemap --output-c-file=src/gfx/door_opened_near_tilemap.c --output-header-file=src/gfx/door_opened_near_tilemap.h obj/gfx/dungeon.png img/door_opened_near.png
img2gb tilemap --name door_closed_near_tilemap --output-c-file=src/gfx/door_closed_near_tilemap.c --output-header-file=src/gfx/door_closed_near_tilemap.h obj/gfx/dungeon.png img/door_closed_near.png

img2gb tilemap --name door_opened_far_tilemap --output-c-file=src/gfx/door_opened_far_tilemap.c --output-header-file=src/gfx/door_opened_far_tilemap.h obj/gfx/dungeon.png img/door_opened_far.png
img2gb tilemap --name door_closed_far_tilemap --output-c-file=src/gfx/door_closed_far_tilemap.c --output-header-file=src/gfx/door_closed_far_tilemap.h obj/gfx/dungeon.png img/door_closed_far.png