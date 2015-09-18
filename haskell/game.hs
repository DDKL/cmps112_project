import System.Random

play :: (Int, Int) -> (Int, Int) -> IO ()
play user prize = do
    if user == prize then return ()
    else do 
        putStrLn $ "How far are you from your prize? " ++ (show $ dist user prize)
        str <- getLine
        let c = head str
        play (processInput c user) prize
        where
            processInput c p@(x, y) = case c of
                'n' -> (x, succ y)
                's' -> (x, pred y)
                'e' -> (succ x, y)
                'w' -> (pred x, y)
                _   -> p
            dist (x1, y1) (x2, y2) = sqrt . sum $ map (^2) diffs 
                where diffs = [fromIntegral (x1-x2), fromIntegral (y1-y2)]

main = do
    putStrLn "Which direction (n,s,e,w) do you head?"
    x  <- randomInt
    y  <- randomInt
    x' <- randomInt
    y' <- randomInt
    play (x, y) (x', y')
    putStrLn "Prize discovered."
    where randomInt = getStdRandom $ randomR (0, 10)
