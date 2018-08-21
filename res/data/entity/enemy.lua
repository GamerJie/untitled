--
-- Created by IntelliJ IDEA.
-- User: Jie
-- Date: 2018/8/14
-- Time: 17:41
-- To change this template use File | Settings | File Templates.
--

return {
    name = "enemy",

    components = {
        Transform = {
            position = {
                x = 100,
                y = 100
            },
            scale = {
                x = 1,
                y = 1
            },
            angle = 0
        },
        Sprite = {
            fileName = "images/sign.png",
        }
    }
}