-- TODO: libraries aren't loaded for actors

-- print('Game object executing! :)')

-- print(fieldOfView)
-- print(gameObjects)


-- NOTE: this will overwrite all captures from Map. TODO: remove
-- Motion
position = { x = 5.0, y = 3.0, z = 2.0 }
direction = { x = 1.0, y = 1.0, z = 1.0 }
speed = 15.0

-- Vision
eyeline = { x = 1.0, y = 0.0, z = 0.0 }
fieldOfView = 80.0
visionDepth = 20.0

-- Physics
bodyRadius = 5.0



function onError()
--    print('[Lua] onError called.')
    return
end

function onSight()
--    print('[Lua] onSight called.')
    return
end

function onCollide()
--    print('[Lua] onCollide called.')
    return
end

function onTargetUpdate()
--    print('[Lua] onTargetUpdate called.')
    return
end

function onAct()
--    print('[Lua] onAct called.')
    return
end