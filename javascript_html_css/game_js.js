(function() {

    var GAME_SIZE = 100; // Dimensions
    
    var chestloc;
    var playerloc;
    
    var $gameend;
    var $distancevalue;

    function Init() {
        $gameend = $('#GameEnd');
        $distancevalue = $('#Distance-Value');
        
        BindEvents();
        NewGame();        
    }
    
            function MovePlayer(direction) {
                var xd = 0;
                var yd = 0;
                switch(direction) {
                    case 'North':
                        yd += 1;
                    break;
                    case 'South':
                        yd -=1;
                    break;
                    case 'West':
                        xd -= 1;
                    break;
                    case 'East':
                        xd += 1;
                    break;
                }
                
                playerloc.x += xd;
                playerloc.y += yd;
                
                CheckDistance();
            }
                function CheckDistance() {
                    // Calculate distance to target
                    var xds = Math.pow((chestloc.x-playerloc.x), 2);
                    var yds = Math.pow((chestloc.y-playerloc.y), 2);
                    var distance = Math.sqrt(xds + yds).toFixed(3);
                    
                    
                    ShowDistance(distance);
                    
                    if(distance == 0) {
                        EndGame();
                    }
                }
                
                    function EndGame() {
                        $gameend.show();
                    }
                    
                    function ShowDistance(distance) {
                        $distancevalue.text(distance);
                    }
                
            function NewGame() {
                GenerateNewGame();
                CheckDistance();
            }
            
                function GenerateNewGame() {
                    // Generate Locations
                    chestloc = {
                        'x': Math.floor(Math.random()*(GAME_SIZE + 1)),
                        'y': Math.floor(Math.random()*(GAME_SIZE + 1))
                    };
                    playerloc = {
                        'x': Math.floor(Math.random()*(GAME_SIZE + 1)),
                        'y': Math.floor(Math.random()*(GAME_SIZE + 1))
                    };
                    
                }
            
            function BindEvents() {
                // Bind Arrow Movement
                $('#Arrows').on({
                    'click': function(e) {
                        e.preventDefault();
                        MovePlayer($(this).data('direction'));
                    }
                }, '.arrow');
                
                // Bind Play Again
                $('#PlayAgain').on({
                    'click': function(e) {
                        e.preventDefault();
                        $gameend.hide();
                        NewGame();
                    }
                });
                
            }
    
    $(function() {
        Init();
    });
})();