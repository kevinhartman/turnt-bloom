print('[Lua] Loading test_map.')


gameActors = {}

local potato = "hi"

local hidden = "hello"

local mushroom = {
    -- Script
    script = loadfile("game/actors/test_actor.lua"),

    capture = {
        myPotato = potato,
        -- Motion
        position = { x = 5.0, y = 3.0, z = 2.0 },
        direction = { x = 1.0, y = 1.0, z = 1.0 },
        speed = 15.0,

        -- Vision
        eyeline = { x = 1.0, y = 0.0, z = 0.0 },
        fieldOfView = 80.0,
        visionDepth = 20.0,

        -- Physics
        bodyRadius = 5.0
    }
}

local star = {
    -- Script
    script = loadfile("game/actors/test_actor.lua"),

    capture = {
        myPotato = potato,
        -- Motion
        position = { x = 5.0, y = 3.0, z = 2.0 },
        direction = { x = 1.0, y = 1.0, z = 1.0 },
        speed = 15.0,

        -- Vision
        eyeline = { x = 1.0, y = 0.0, z = 0.0 },
        fieldOfView = 80.0,
        visionDepth = 20.0,

        -- Physics
        bodyRadius = 5.0
    }
}

gameActors[1] = mushroom
gameActors[2] = star

print("[Lua] Loaded test_map.")