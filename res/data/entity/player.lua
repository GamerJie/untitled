
return {
    name = "player";

    components = {
        Transform = {
            position = {
                x = 400,
                y = 300
            },
            scale = {
                x = 2,
                y = 2
            },
            angle = 0
        },

        Sprite = {
            fileName = "images/character.png",
            rect = { 0, 0, 32, 32 },
            animations = {
                idle = {
                    start = 0,
                    length = 2,
                    timer = 0.3
                },
                run = {
                    start = 2,
                    length = 2,
                    timer = 0.2
                }
            }
        }
    }
}