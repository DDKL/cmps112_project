import System.Random

play :: (Int, Int) -> (Int, Int) -> IO ()
play user treasure = do
    if user == treasure then return ()
    else do 
        putStrLn $ "Distance to your treasure: " ++ (show $ distance user treasure)
        str <- getLine
        let c = head str
        play (processInput c user) treasure
        where
            processInput c p@(x, y) = case c of
                'n' -> (x, succ y)
                's' -> (x, pred y)
                'e' -> (succ x, y)
                'w' -> (pred x, y)
                _   -> p
            distance (x1, y1) (x2, y2) = sqrt . sum $ map (^2) diffs 
                where diffs = [fromIntegral (x1-x2), fromIntegral (y1-y2)]

main = do
    putStrLn "Which direction (n,s,e,w) do you head?"
    x  <- randomInt
    y  <- randomInt
    x' <- randomInt
    y' <- randomInt
    play (x, y) (x', y')
    putStrLn "You found the treasure. Nice!"
    where randomInt = getStdRandom $ randomR (0, 10)