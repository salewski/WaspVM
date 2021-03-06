 0φ       
	    
	   	  
D
	     (
	  
	        B
	  	       ;
	    A
	    C   
 wύ 
	       
	   q
	   
	    
      
	            ͺύ 
	       
	   €
	   
	    
      
	           
	     
	       
	     
	  
	 !  " 
	        #  $  
	   % 
	     
	  
	 !  & 
	        
	   '  $       
	   '  'd
	   ( 
	     
	   )  *  
	     *  
	   + 
	    
	   ,    
	   -  *  
	   . 
	   /  *    *            	filter -- A process that waits for data from an input channel, and 
           sends data to an output channel.  Filters are constructed using
           a constructor function, then wired together using either the 
           input-chain or output-chain functions.input-chain -- The input-chain function, given an input channel and zero or 
                more filters, connects the filters together in such a way that 
                when a message is sent to the input channel, it will propagate
                through the filters until it arrives in a final output channel.
               
                This output channel is returned by the input-chain function.±output-chain -- The output-chain function, given an output channel and zero 
                 or more filters, connects the filters together in such a 
                 way that when a message is sent to the input channel, it 
                 will propagate through the filters until it arrives in a 
                 final output channel.
               
                 This input channel is returned by the input-chain function.error-on-fail -- Given a message, raises an error if a failure was signalled,
               using the (fail info ...) or (fail info ... error) convention.
               If the later convention is used, the error's context will match
               the original context of the error. ώfail-on-error -- Given a channel and zero or more statements, guards the
               evaluation of the statements with a function that will send
               a (fail info ... error) message to the specified channel if
               an error occurs. module 
lib/filter import lib/iterate error-on-fail pair? eq? car fail find error? re-error error output-chain output for-each chain-filter 
make-queue queue-input queue-output input-chain input 
set-macro! define-filter list define function make-symbol mk- in out spawn run- fail-on-error guard fail-for-error err send quote 	error-key scatter 
error-info