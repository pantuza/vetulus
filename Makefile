#
#
# Vetulus Makefile
#
#


help:
	@echo "Vetulus Target rules:"
	@echo "start        Runs docker composition"
	@echo "stop         Clens and stops docker composition"
	@echo "logs         Follow Vetulus logs"
	@echo "clean        Cleans project compilation"
	@echo "test         Runs Vetulus tests"
	@echo "shell        Run a shell inside Vetulus container"
	@echo "recompile    Recompile all modules"


start:
	@echo "Running Vetulus services"
	@docker-compose up --detach


stop:
	@echo "Stoping Vetulus services"
	@docker-compose down


logs:
	@docker logs --tail 100 --follow vetulus


clean:
	@echo "Cleaning project.."
	@docker exec -it vetulus bash -c 'find {manager,config,services} -type d -iname build | xargs rm -rvf'


test:
	@echo "Running Vetulus tests"
	@docker exec -it vetulus scripts/run_tests.sh


shell:
	@docker exec -it vetulus bash


recompile:
	@docker exec -it vetulus scripts/recompile.sh
