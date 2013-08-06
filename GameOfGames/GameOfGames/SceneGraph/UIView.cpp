#include "UIView.h"
#include "..\UIViewClickListener.h"
#include "..\AssetManager.h"

UIView::UIView(sf::Vector2i* newSize, std::string newTexture)
{
	setSize(newSize);
	focusable = true;
	setTexture(newTexture);
}

UIView::UIView(sf::Vector2i* newSize)
{
	setSize(newSize);
	focusable = true;
}

void UIView::activated()
{
	if(listener)
	{
		listener->viewClicked(this);
	}
}

void UIView::setClickListener(UIViewClickListener* newListener)
{
	listener = newListener;
}

void UIView::onRemoveTexture()
{
	adjustBackGround();
}

void UIView::setSize(sf::Vector2i* newSize)
{
	size = newSize;

	adjustBackGround();
}

void UIView::onDraw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform, bool clickTest)
{
	SpriteNode::onDraw(deltaTime,target, parentTranform, clickTest);

	if(focusable && clickTest)
	{
		sf::FloatRect temp = sf::FloatRect(0.f,0.f,float(size->x),float(size->y));

		sf::Transform inverse = parentTranform.getInverse();

		sf::Vector2i mousePos = *InputHandlerSFML::getInstance()->getMousePosition();

		sf::Vector2f transformedPoint = inverse.transformPoint(mousePos.x,mousePos.y);

		if(temp.contains(transformedPoint))
		{
			AssetManager::getInstance()->setDrawnClickable(this);
		}
	}	
}

void UIView::onSetTexture()
{
	adjustBackGround();
}

void UIView::adjustBackGround()
{
	sf::RenderTexture destinationTexture= sf::RenderTexture();

	destinationTexture.create(size->x,size->y);

	destinationTexture.clear(sprite->getColor());

	if(texture)
	{
		int tileSize = texture->getSize().x/3;

		if (tileSize*2 > size->x || tileSize*2 > size->y)
		{
			std::cout<< "Size of view too small for texture selected.\n";
		}
		else
		{
			destinationTexture.clear();

			sf::Sprite tempSprite = sf::Sprite();
			tempSprite.setTexture(*texture);

			int verticalFillSpace = size->y;
			int verticalDrawingPoint = 0;

			while (verticalFillSpace > 0)
			{
				int referenceVerticalPoint = 0;

				//are we not filling the first line?
				if(verticalDrawingPoint)
				{
					//are we filling the bottom?
					if (verticalFillSpace <= tileSize)
					{
						referenceVerticalPoint = tileSize*2;
					}
					else
					{
						referenceVerticalPoint = tileSize;
					}
				}

				//we draw the left chunk
				tempSprite.setPosition(0.f,float(verticalDrawingPoint));
				tempSprite.setTextureRect(sf::IntRect(0,referenceVerticalPoint,tileSize,tileSize));
				destinationTexture.draw(tempSprite);

				//the right chunk
				tempSprite.setPosition(float(size->x-tileSize),float(verticalDrawingPoint));
				tempSprite.setTextureRect(sf::IntRect(tileSize*2,referenceVerticalPoint,tileSize,tileSize));
				destinationTexture.draw(tempSprite);

				int horizontalFillingSpace = size->x - (tileSize*2);
				int horizontalDrawingPoint = tileSize;

				tempSprite.setTextureRect(sf::IntRect(tileSize,referenceVerticalPoint,tileSize,tileSize));

				//now we fill the horizontal gap
				while (horizontalFillingSpace > 0)
				{
					//are we drawing the last one?
					if (horizontalFillingSpace<tileSize)
					{
						tempSprite.setTextureRect(sf::IntRect(tileSize,referenceVerticalPoint,horizontalFillingSpace,tileSize));
					}

					tempSprite.setPosition(float(horizontalDrawingPoint),float(verticalDrawingPoint));
					destinationTexture.draw(tempSprite);

					horizontalDrawingPoint +=tileSize;
					horizontalFillingSpace -= tileSize;
				}

				verticalFillSpace -= tileSize;

				if (verticalFillSpace < tileSize)
				{
					verticalDrawingPoint += verticalFillSpace;
				}
				else
				{
					verticalDrawingPoint += tileSize;
				}
			}
		}
	}

	destinationTexture.display();

	if(finalTexture)
	{
		delete finalTexture;
	}

	finalTexture = new sf::Texture(destinationTexture.getTexture());

	finalTexture->setSmooth(true);

	sprite->setTexture(*finalTexture);
}

UIView::~UIView(void)
{
	if (finalTexture)
	{
		delete finalTexture;
	}

	if (size)
	{
		delete size;
	}
}