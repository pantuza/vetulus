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
	@echo "compile      Compile all modules"
	@echo "build        Builds docker image locally"
	@echo "image        Merges master into docker branch and pushes to remote"


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


compile:
	@docker exec -it vetulus scripts/compile.sh


build: Dockerfile
	@docker build . --tag vetulus


image:
	@git checkout master;
	@git pull origin master --rebase;
	@git checkout docker;
	@git pull origin docker --rebase;
	@git merge master --no-commit;
	@git push origin docker;
	@git checkout master;
